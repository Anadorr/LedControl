using System;
using NUnit.Framework;
using FluentAssertions;
using System.Linq;
using System.Collections.Generic;

namespace LedControl.Test
{
	public class TestCaseFactory
	{
		private static readonly List<ActionParams> TestData = new List<ActionParams> {
			new ActionParams(AllowedLedActions.STROBE_UNEVEN, RGBColors.COLOR_BLACK, RGBColors.COLOR_WHITE, 0, 1000, 0, 10, 1, 0, 0),
			new ActionParams(AllowedLedActions.STROBE_UNEVEN, RGBColors.COLOR_WHITE, RGBColors.COLOR_BLUE, 0, 1000, 0, 10, 1, 0, 0),
			new ActionParams(AllowedLedActions.STROBE_UNEVEN, RGBColors.COLOR_BLACK, RGBColors.COLOR_HMAGENTA, 0, 5000, 0, 1, 1, 0.5f, 0),
			new ActionParams(AllowedLedActions.STROBE_UNEVEN, RGBColors.COLOR_BLACK, RGBColors.COLOR_ORANGE, 0, 1000, 500, 5, 1, 0.5f, 0.5f),
			new ActionParams(AllowedLedActions.STROBE_UNEVEN, RGBColors.COLOR_BLACK, RGBColors.COLOR_RED, 1000, 1000, 0, 10, 1, 0.3f, 0.1f),
			new ActionParams(AllowedLedActions.STROBE_UNEVEN, RGBColors.COLOR_WHITE, RGBColors.COLOR_HGREEN, 2000, 5000, 1500, 10, 1, 0.7f, 0),
			new ActionParams(AllowedLedActions.STROBE_UNEVEN, RGBColors.COLOR_HRED, RGBColors.COLOR_HGREEN, 3000, 1000, 3000, 1, 1, 0.888f, 0),
			new ActionParams(AllowedLedActions.STROBE_UNEVEN, RGBColors.COLOR_PINK, RGBColors.COLOR_WHITE, 1000000, 1000000, 20000, 10, 1, 0, 0.5f),
		};
		
		public static IEnumerable<ActionParams> TestCases
		{
			get
			{
				var strobeTestCases = new List<ActionParams> ();
				var cnt = TestData.Count;
				for (int i=0; i<cnt; i++) 
				{
					// Add the same set of 'strobe' actions
					var strobeData = new ActionParams (TestData[i]);
					strobeData.action = AllowedLedActions.STROBE;
					strobeData.upPct = 0.5f;
					strobeData.maxColorPct = 0;

					strobeTestCases.Add (strobeData);
				}

				foreach (var testCase in TestData.Concat(strobeTestCases)) {
					yield return testCase;
				}
			}
		}  
	}

	/// <summary>
	/// Combined tests of Strobe and Strobe Uneven
	/// </summary>
	[TestFixture ()]
	public class StrobeUnevenTest
	{
		public StrobeUnevenTest() {
			
		}

		/// <summary>
		/// Strobe should be ascending, then stay at max brightness, then descending
		/// </summary>
		[TestCaseSource(typeof(TestCaseFactory), "TestCases")]
		public void Strobe_Should_BeInOrder(ActionParams actionData)
		{
			var sut = new LedWrapper ();

			var result = sut.GetActionOutput (actionData);
			// ascending
			int i = 0;
			if (actionData.upPct != 0) result [0].Should ().Be (actionData.colorFrom);

			while (i < actionData.effectiveResultsCount * actionData.upPct)
			{
				result [i + 1].IsCloserOrSameTo (actionData.colorTo, result [i]).Should ().BeTrue ();
				i++;
			}

			// max brightness
			while (i < actionData.effectiveResultsCount * (actionData.upPct + actionData.maxColorPct))
			{
				result [i].Should ().Be (actionData.colorTo);
				i++;
			}

			// descending
			while (i < actionData.effectiveResultsCount - 1)
			{
				result [i + 1].IsCloserOrSameTo (actionData.colorFrom, result[i]).Should ().BeTrue ();
				i++;
			}
			if (actionData.upPct + actionData.maxColorPct < 1) result [actionData.effectiveResultsCount].Should ().Be (actionData.colorFrom);
		}

		[TestCaseSource(typeof(TestCaseFactory), "TestCases")]
		public void Strobe_Should_ShowBlack_AfterEnd(ActionParams actionData)
		{
			var sut = new LedWrapper ();

			var result = sut.GetActionOutput (actionData);

			var afterEndElemets = result.Skip (actionData.effectiveResultsCount + 1).ToList ();
			afterEndElemets.Count.Should ().Be (actionData.afterEndResultsCount);
			if (actionData.afterEndResultsCount > 0) afterEndElemets.Should ().OnlyContain (c => c.Equals(RGBColors.COLOR_BLACK));
		}
	}
}

