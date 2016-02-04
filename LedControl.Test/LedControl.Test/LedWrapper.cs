using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

namespace LedControl.Test
{
	public enum AllowedLedActions {
		COLOR_CHANGE, STROBE, STROBE_UNEVEN, STROBE_CYCLE, STROBE_CYCLE_BRIGHTPERIOD, STROBE_CYCLE_UNEVEN, STROBE_RAINBOW, FULL_RAINBOW, FULL_RAINBOW_TO_HALF, STROBE_RAINBOW_SHIFT, STROBE_RAINBOW_HALF
	};


	public class LedWrapper
	{
		[DllImport("../../../../LedControl/bin/Debug/libLedControl.so", CallingConvention = CallingConvention.Cdecl)]
		private static extern int GetActionOutput (uint action, out int size, out IntPtr data, RGB colorFrom, RGB colorTo, int startTime, int duration, int delayAfter, int tickLength, int count, float upPct, float maxColorPct, float firstColorPct, float secondColorPct);

		public List<RGB> GetActionOutput(ActionParams actiondata) 
		{
			int size = 0;
			IntPtr data = IntPtr.Zero;
			int errorCode = 0;
			errorCode = GetActionOutput ((uint)actiondata.action, out size, out data, actiondata.colorFrom, actiondata.colorTo, actiondata.startTime, actiondata.duration,
				actiondata.delayAfter, actiondata.tickLength, actiondata.count, actiondata.upPct, actiondata.maxColorPct, actiondata.firstColorPct, actiondata.secondColorPct);
			// We can't catch exceptions thrown in native code so we return errorCode instead
			if (errorCode != 0) {
				throw new Exception (string.Format ("Got error {0} in native code", errorCode));
			}
			var result = new List<RGB> ();

			/*byte[] buffer = new byte[size * 3];
			Marshal.Copy (data, buffer, 0, buffer.Length);*/

			var structSize = Marshal.SizeOf (typeof(RGB));
			for (int i = 0; i < size; i++) {
				var valuePtr = new IntPtr(data.ToInt64() + structSize * i);
				RGB tmpVal = (RGB)Marshal.PtrToStructure(valuePtr, typeof(RGB));
				result.Add(tmpVal);
			}

			return result;
		}
	}
}

