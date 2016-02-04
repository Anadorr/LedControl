using System;
using System.Runtime.InteropServices;

namespace LedControl.Test
{
	[StructLayout(LayoutKind.Sequential)]
	public struct RGB
	{
		public byte r;
		public byte g;
		public byte b;

		public RGB(byte red, byte green, byte blue) {
			r = red;
			g = green;
			b = blue;
		}

		public override bool Equals(object o) 
		{
			if (o is RGB) {
				var c = (RGB)o;
				return c.r == r && c.g == g && c.b == b;
			} else {
				return false;
			}
		}

		public override int GetHashCode ()
		{
			return new { r,g,b }.GetHashCode ();
		}
			
		/*public static bool operator < (RGB c1, RGB c2) 
		{
			return c1.r < c2.r && c1.g < c2.g && c1.b < c2.b;
		}

		public static bool operator > (RGB c1, RGB c2) 
		{
			return c1.r > c2.r && c1.g > c2.g && c1.b > c2.b;
		}*/

		public static RGB operator + (RGB c1, RGB c2) {
			return c1.Add (c2);
		}

		public static RGB operator * (RGB c1, double percent) {
			return c1.Multiply (percent);
		}

		public static RGB operator - (RGB c1, RGB c2) {
			return c2.AbsoluteDifference (c1);
		}

		public RGB Add (RGB c2) {
			Func<byte, byte, byte> addOrMax = (b1, b2) => (b1 + b2 > byte.MaxValue ? byte.MaxValue : (byte)(b1 + b2));
			return new RGB (addOrMax(r,c2.r), addOrMax(g, c2.g), addOrMax(b, c2.b));
		}

		private RGB Multiply (double percent) 
		{
			if (percent > 1) {
				throw new ArgumentException("percent should not be higher than 1.0");
			}
			return new RGB ((byte)(r * percent), (byte)(g * percent), (byte)(b * percent));
		}

		public bool Precedes(RGB c2) {
			return r < c2.r && g < c2.g && b < c2.b;
		}

		public bool Follows(RGB c2) {
			return r > c2.r && g > c2.g && b > c2.b;
		}

		/// <summary>
		/// Checks if current color is not further from target color than c2.
		/// </summary>
		/// <returns><c>true</c> if each color component of current color is not further from target color than c2; otherwise, <c>false</c>.</returns>
		/// <param name="c2">Color to compare to.</param>
		/// <param name="target">Target color.</param>
		public bool IsCloserOrSameTo(RGB target, RGB c2) {
			Func<byte, byte, byte, bool> inBetween = (t, b1, b2) => Math.Max(b1, b2) >= t && t >= Math.Min(b1,b2);
			return (
				inBetween(r, target.r, c2.r) &&
				inBetween(g, target.g, c2.g) &&
				inBetween(b, target.b, c2.b));
		}

		/// <summary>
		/// Returns new color which is closer to target color by certain percent (0% - current color, 100% - target color);
		/// </summary>
		/// <returns>New color.</returns>
		/// <param name="target">Target.</param>
		/// <param name="percent">Percent.</param>
		public RGB MoveCloserTo(RGB target, double percent) {
			if (percent > 1) {
				throw new ArgumentException("percent should not be higher than 1.0");
			}
			Func<byte, byte, double, byte> moveByteCloserTo = (b1, b2, pct) => (byte)(b1 + (b2 - b1) * pct);
			return new RGB (moveByteCloserTo(r, target.r, percent), moveByteCloserTo(g, target.g, percent), moveByteCloserTo(b, target.b, percent));
		}

		/// <summary>
		/// Returns absolute difference between colors on all color componens.
		/// </summary>
		/// <returns></returns>
		/// <param name="target">Target color.</param>
		public RGB AbsoluteDifference(RGB target) {
			return new RGB((byte)Math.Abs (target.r - r), (byte)Math.Abs (target.g - g), (byte)Math.Abs (target.b - b));
		}

		/// <summary>
		/// Returns maximum absolute difference on any color component.
		/// </summary>
		/// <returns></returns>
		/// <param name="target">Target color.</param>
		public byte MaxDifference(RGB target)
		{
			return Math.Max(Math.Max((byte)Math.Abs (target.r - r), (byte)Math.Abs (target.g - g)), (byte)Math.Abs (target.b - b));
		}

		public override string ToString ()
		{
			return string.Format ("{0}, {1}, {2}", r, g, b);
		}
	}
}

