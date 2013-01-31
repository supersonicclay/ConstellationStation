using System;

namespace ConstellationStation.Common
{
    /// <summary>
    /// Storage for declination (vertical) position.
    /// </summary>
    public struct Declination
    {
        // Fields
        /// <summary>
        /// Backing store.
        /// </summary>
        private int degrees;
        /// <summary>
        /// Backing store.
        /// </summary>
        private int minutes;
        /// <summary>
        /// Backing store.
        /// </summary>
        private bool positive;
        /// <summary>
        /// Backing store.
        /// </summary>
        private float seconds;

        // Properties
        /// <summary>
        /// Gets or sets whether or not this declination is positive.
        /// </summary>
        public bool Positive
        {
            get { return positive; }
            set { positive = value; }
        }
        /// <summary>
        /// Gets or sets the number of degrees.
        /// </summary>
        /// <exception cref="T:ArgumentOutOfRangeException">Attempting to set to a value less than 0 or greater than 90.</exception>
        public int Degrees
        {
            get { return degrees; }
            set
            {
                if (value > 90.0f || value < 0.0f)
                {
                    throw new ArgumentOutOfRangeException();
                }
                degrees = value;
            }
        }
        /// <summary>
        /// Gets or sets the number of minutes.
        /// </summary>
        /// <exception cref="T:ArgumentOutOfRangeException">Attempting to set to a value less than 0 or greater than 60.</exception>
        public int Minutes
        {
            get { return minutes; }
            set
            {
                if (value > 60.0f || value < 0.0f)
                {
                    throw new ArgumentOutOfRangeException();
                }
                minutes = value;
            }
        }
        /// <summary>
        /// Gets or sets the number of seconds (including the decimal portion).
        /// </summary>
        /// <exception cref="T:ArgumentOutOfRangeException">Attempting to set to a value less than 0 or greater than 60.</exception>
        public float Seconds
        {
            get { return seconds; }
            set
            {
                if (value > 60.0f || value < 0.0f)
                {
                    throw new ArgumentOutOfRangeException();
                }
                seconds = value;
            }
        }

        // Methods
        /// <summary>
        /// Returns a new instance of <see cref="T:Declination"/> by parsing <paramref name="declinationString"/>.
        /// </summary>
        /// <param name="declinationString">A string representing a declination.</param>
        /// <returns>A new instance of <see cref="T:Declination"/> by parsing <paramref name="declinationString"/>.</returns>
        /// <remarks><paramref name="declinationString"/> must have a format of "PDD MM SS.S" where
        /// P is "+" or "-", DD is the degrees, MM is the minutes, and SS.S is the seconds.</remarks>
        public static Declination Parse(string declinationString)
        {
            Declination declination = new Declination();
            declination.Positive = declinationString.StartsWith("+");
            declination.Degrees = Convert.ToInt32(declinationString.Substring(1, 3));
            declination.Minutes = Convert.ToInt32(declinationString.Substring(4, 3));
            declination.Seconds = Convert.ToSingle(declinationString.Substring(7));
            return declination;
        }
    }
}
