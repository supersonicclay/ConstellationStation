using System;

namespace ConstellationStation.Math
{
    /// <summary>
    /// Contains methods for performing interpolations.
    /// </summary>
    public static class Interpolations
    {
        /// <summary>
        /// Returns a value between <paramref name="value1"/> and <paramref name="value2"/> (inclusive)
        /// using linear interpolation. When <paramref name="ratio"/> is 0, <paramref name="value1"/> is
        /// returned. When <paramref name="ratio"/> is 1, <paramref name="value2"/> is returned.
        /// </summary>
        /// <param name="ratio">A number between 0 and 1 (inclusive).</param>
        /// <param name="value1">A number indicating the first limit.</param>
        /// <param name="value2">A number indicating the second limit.</param>
        /// <returns>A value between <paramref name="value1"/> and <paramref name="value2"/> (inclusive) using linear interpolation.</returns>
        /// <exception cref="T:ArgumentOutOfRangeException"><paramref name="ratio"/> is less than 0 or greater than 1.</exception>
        public static float Lerp(float ratio, float value1, float value2)
        {
            if (ratio < 0.0f || ratio > 1.0f)
            {
                throw new ArgumentOutOfRangeException("ratio", "ratio must be between 0 and 1 (inclusive)");
            }
            return value1 + (ratio * (value2 - value1));
        }
    }
}
