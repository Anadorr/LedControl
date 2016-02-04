using NUnit.Framework;
using System;
using FluentAssertions;
using System.Collections.Generic;
using System.Linq;

namespace LedControl.Test
{
	[TestFixture ()]
	public class ColorChangeTest
	{
		private static readonly List<ActionParams> TestData = new List<ActionParams> {
			new ActionParams(AllowedLedActions.COLOR_CHANGE, RGBColors.COLOR_BLACK, RGBColors.COLOR_WHITE, 0, 1000, 0, 10),
			new ActionParams(AllowedLedActions.COLOR_CHANGE, RGBColors.COLOR_GREEN, RGBColors.COLOR_HMAGENTA, 0, 5000, 0, 1),
			new ActionParams(AllowedLedActions.COLOR_CHANGE, RGBColors.COLOR_BLACK, RGBColors.COLOR_ORANGE, 0, 1000, 500, 5),
			new ActionParams(AllowedLedActions.COLOR_CHANGE, RGBColors.COLOR_PINK, RGBColors.COLOR_WHITE, 1000, 1000, 0, 10),
			new ActionParams(AllowedLedActions.COLOR_CHANGE, RGBColors.COLOR_HVIOLET, RGBColors.COLOR_BLACK, 2000, 5000, 1500, 10),
			new ActionParams(AllowedLedActions.COLOR_CHANGE, RGBColors.COLOR_HGREEN, RGBColors.COLOR_HORANGE, 3000, 1000, 3000, 1),
			new ActionParams(AllowedLedActions.COLOR_CHANGE, RGBColors.COLOR_BLACK, RGBColors.COLOR_WHITE, 1000000, 10000, 20000, 10),
		};

		/// <summary>
		/// Color change should be either ascending or descending.
		/// </summary>
		[TestCaseSource("TestData")]
		public void ColorChange_Should_BeInOrder(ActionParams actionData)
		{
			var sut = new LedWrapper ();

			var result = sut.GetActionOutput (actionData);

			for (int i = 1; i < actionData.effectiveResultsCount; i++) 
			{
				result [i].IsCloserOrSameTo (actionData.colorTo, result [i - 1]).Should ().BeTrue ();
			}
		}

		/// <summary>
		/// Color change should uniformly cover all colors in the range.
		/// </summary>
		[TestCaseSource("TestData")]
		public void ColorChange_Should_SpanColorRange(ActionParams actionData)
		{
			var sut = new LedWrapper ();

			var result = sut.GetActionOutput (actionData);

			// detemining that ColorChange spans color range uniformly is tricky because of dynamic precision in C++ code
			// Instead, verify that increments happen uniformly and that start, middle and end colors are correct

			result [0].Should ().Be (actionData.colorFrom);
			result [actionData.effectiveResultsCount / 2].MaxDifference (actionData.colorFrom.MoveCloserTo (actionData.colorTo, 0.5)).Should ().BeLessOrEqualTo (2, "Middle color can be different only by a small margin");
			result [actionData.effectiveResultsCount - 1].Should ().Be (actionData.colorTo);

			List<int> diffs = new List<int> ();
			for (int i = 1; i < actionData.effectiveResultsCount; i++) 
			{
				var delta = result [i].MaxDifference (result [i - 1]);
				diffs.Add (delta);
			}
			var notNullDiffs = diffs.Where (i => i != 0).ToList();
			(notNullDiffs.Average() - notNullDiffs.Max()).Should ().BeLessThan (2, "Color increments should be uniform and can vary only due to rounding errors"); 
			(notNullDiffs.Average() - notNullDiffs.Min()).Should ().BeLessThan (2);

			var minDifferentValuesCount = actionData.duration / (Math.Max (actionData.tickLength, 32)); // precision is never less than 32ms
			notNullDiffs.Count.Should ().BeGreaterOrEqualTo (Math.Min(actionData.colorTo.MaxDifference(actionData.colorFrom) / 2, minDifferentValuesCount - 2));
		}

		[TestCaseSource("TestData")]
		public void ColorChange_Should_ShowBlack_AfterEnd(ActionParams actionData)
		{
			var sut = new LedWrapper ();

			var result = sut.GetActionOutput (actionData);

			var afterEndElemets = result.Skip (actionData.effectiveResultsCount + 1).ToList ();
			afterEndElemets.Count.Should ().Be (actionData.afterEndResultsCount);
			if (actionData.delayAfter > 0) afterEndElemets.Should ().OnlyContain (c => c.Equals(RGBColors.COLOR_BLACK));
		}
	}
}

