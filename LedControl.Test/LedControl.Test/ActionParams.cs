using System;

namespace LedControl.Test
{
	public class ActionParams
	{
		public AllowedLedActions action { get; set;}
		public RGB colorFrom {get; set;}
		public RGB colorTo {get; set;}
		public int startTime {get; set;}
		public int duration {get; set;}
		public int delayAfter {get; set;}
		public int tickLength {get; set;}
		public int count {get; set;} = 1;
		public float upPct {get; set;} = 0.5f;
		public float maxColorPct {get; set;} = 0;
		public float firstColorPct {get; set;}= 0.33f;
		public float secondColorPct{get; set;} = 0.33f;

		public int effectiveResultsCount {get {return duration / tickLength;} }
		public int afterEndResultsCount {get {return delayAfter / tickLength;} }

		public ActionParams(AllowedLedActions action, RGB colorFrom, RGB colorTo, int startTime, int duration, int delayAfter, int tickLength) {
			this.action = action;
			this.colorFrom = colorFrom;
			this.colorTo = colorTo;
			this.startTime = startTime;
			this.duration = duration;
			this.delayAfter = delayAfter;
			this.tickLength = tickLength;
		}
		public ActionParams(AllowedLedActions action, RGB colorFrom, RGB colorTo, int startTime, int duration, int delayAfter, int tickLength
			, int count = 1, float upPct = 0.5f, float maxColorPct = 0, float firstColorPct = 0.33f, float secondColorPct = 0.33f):
		this(action, colorFrom, colorTo, startTime, duration, delayAfter, tickLength)
		{
			this.count = count;
			this.upPct = upPct;
			this.maxColorPct = maxColorPct;
			this.firstColorPct = firstColorPct;
			this.secondColorPct = secondColorPct;
		}

		public ActionParams(ActionParams data) 
		{
			this.action = data.action;
			this.colorFrom = data.colorFrom;
			this.colorTo = data.colorTo;
			this.startTime = data.startTime;
			this.duration = data.duration;
			this.delayAfter = data.delayAfter;
			this.tickLength = data.tickLength;
			this.count = data.count;
			this.upPct = data.upPct;
			this.maxColorPct = data.maxColorPct;
			this.firstColorPct = data.firstColorPct;
			this.secondColorPct = data.secondColorPct;

		}
	}
}

