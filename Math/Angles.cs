using ConstellationStation.Common;
using Microsoft.DirectX;

namespace ConstellationStation.Math
{
    /// <summary>
    /// Module containing mathematical methods related to angles.
    /// </summary>
    public static class Angles
    {
        /// <summary>
        /// Converts <paramref name="degrees"/> degrees to radians.
        /// </summary>
        /// <param name="degrees">A number, in degrees, to be converted to radians.</param>
        /// <returns><paramref name="degrees"/> converted to radians.</returns>
        public static float DegreesToRadians(float degrees)
        {
            return (float) (degrees * (System.Math.PI / 180));
        }
        /// <summary>
        /// Sets the equatorial coordinates <paramref name="equitorial"/>
        /// based on the spherical coordinates <paramref name="spherical"/>.
        /// </summary>
        /// <param name="equitorial">To be set to the equitorial coordinates form of <paramref name="spherical"/>.</param>
        /// <param name="spherical">The spherical coordinates.</param>
        public static void EquatorialFromSpherical(out EquitorialCoordinates equitorial, SphericalCoordinates spherical)
        {
            equitorial = new EquitorialCoordinates();
            equitorial.RightAscension = new RightAscension();
            equitorial.Declination = new Declination();

            float degrees, hours, minutes;
            // Convert phi to declination form
            // At this point:    0 <= phi <= PI.
            // Need it to be:   90 <= deg <= -90. (for declination)
            degrees = 90.0f - RadiansToDegrees(spherical.Phi);
            equitorial.Declination.Positive = true;
            if (degrees < 0.0f)
            {
                equitorial.Declination.Positive = false;
                degrees = -degrees;
            }
            minutes = (degrees - (int)degrees) * 60;
            equitorial.Declination.Seconds = (minutes - (int)minutes) * 60;
            equitorial.Declination.Minutes = (int)minutes;
            equitorial.Declination.Degrees = (int)degrees;

            // Convert theta to right ascension form
            degrees = spherical.Theta == 0.0f ? 0.0f : 360.0f - RadiansToDegrees(spherical.Theta); // RA and theta are measured in opposite directions
            hours = (float)(degrees / 15.0f);
            minutes = (hours - (int)hours) * 60;
            equitorial.RightAscension.Seconds = (minutes - (int)minutes) * 60;
            equitorial.RightAscension.Minutes = (int)minutes;
            equitorial.RightAscension.Hours = (int)hours;
        }
        /// <summary>
        /// Converts <paramref name="radians"/> radians to degrees.
        /// </summary>
        /// <param name="radians">A number, in radians, to be converted to degrees.</param>
        /// <returns><paramref name="radians"/> converted to degrees.</returns>
        public static float RadiansToDegrees(float radians)
        {
            return (float)(radians * (180 / System.Math.PI));
        }
        /// <summary>
        /// Sets the spherical coordinates <paramref name="spherical"/>
        /// based on the equatorial coordinates <paramref name="equitorial"/>.
        /// </summary>
        /// <param name="spherical">To be set to the spherical coordinates based on <paramref name="equitorial"/>.</param>
        /// <param name="equitorial">To equitorial coordinates.</param>
        public static void SphericalFromEquatorial(out SphericalCoordinates spherical, EquitorialCoordinates equitorial)
        {
            spherical = new SphericalCoordinates();
            // Calculate phi
            double radians = DegreesToRadians(equitorial.Declination.Degrees + (equitorial.Declination.Minutes + equitorial.Declination.Seconds / 60) / 60);
            if (equitorial.Declination.Positive)
                spherical.Phi = (float)((System.Math.PI / 2) - radians);
            else
                spherical.Phi = (float)((System.Math.PI / 2) + radians);

            // Calculate theta
            radians = (float)(System.Math.PI * 2 * (equitorial.RightAscension.Hours + (equitorial.RightAscension.Minutes + equitorial.RightAscension.Seconds / 60) / 60) / 24);
            spherical.Theta = radians == 0.0f ? 0.0f : (float)(System.Math.PI * 2 - radians); // RA and theta are measured in opposite directions
        }
        /// <summary>
        /// Sets the spherical coordinates <paramref name="spherical"/>
        /// based <paramref name="vector"/> containing x, y, and z coordinates.
        /// </summary>
        /// <param name="spherical">To be set to the spherical coordinates.</param>
        /// <param name="vector">Vector containing x, y, and z coordinates.</param>
        public static void SphericalFromVector3(out SphericalCoordinates spherical, Vector3 vector)
        {
            spherical = new SphericalCoordinates();

            /// Phi is measured from 0 (north) to PI (south).
            /// Theta is measured from 0 to 2*PI degrees
            spherical.Phi = (float)System.Math.Acos((double)vector.Y);

            if (vector.Z == 0.0f && vector.X == 0.0f)  // Prevent divide by 0
            {
                spherical.Theta = 0.0f;
                return;
            }
            if (vector.Z >= 0)
            {
                spherical.Theta = (float)System.Math.Asin(vector.X / System.Math.Sqrt((double)(vector.Z * vector.Z) + (vector.X * vector.X)));
            }
            else
            {
                spherical.Theta = (float)(System.Math.PI - System.Math.Asin(vector.X / System.Math.Sqrt((double)(vector.Z * vector.Z) + (vector.X * vector.X))));
            }

            if (spherical.Theta < 0.0f)
            {
                spherical.Theta += (float)(2 * System.Math.PI);	// Prevent negative theta
            }
        }
        /// <summary>
        /// Sets the x, y, and z coordinates of <paramref name="vector"/> based on the
        /// spherical coordinates <paramref name="spherical"/>.
        /// </summary>
        /// <param name="vector">To be set to a vector containing the x, y, and z coordinates.</param>
        /// <param name="spherical">The spherical coordinates.</param>
        public static void Vector3FromSpherical(out Vector3 vector, SphericalCoordinates spherical)
        {
            vector.X = (float)(System.Math.Sin(spherical.Phi) * System.Math.Sin(spherical.Theta));
            vector.Y = (float)(System.Math.Cos(spherical.Phi));
            vector.Z = (float)(System.Math.Sin(spherical.Phi) * System.Math.Cos(spherical.Theta));
        }
    }
}
