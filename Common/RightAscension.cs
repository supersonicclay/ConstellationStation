using System;

namespace ConstellationStation.Common
{
    /// <summary>
    /// Storage for right ascension (horizontal) position.
    /// </summary>
    public struct RightAscension
    {
        // Fields
        /// <summary>
        /// Backing store.
        /// </summary>
        private int hours;
        /// <summary>
        /// Backing store.
        /// </summary>
        private int minutes;
        /// <summary>
        /// Backing store.
        /// </summary>
        private float seconds;

        // Properties
        /// <summary>
        /// Gets or sets the number of hours.
        /// </summary>
        /// <exception cref="T:ArgumentOutOfRangeException">Attempting to set to a value less than 0 or greater than 24.</exception>
        public int Hours
        {
            get { return hours; }
            set
            {
                if (value > 24.0f || value < 0.0f)
                {
                    throw new ArgumentOutOfRangeException();
                }
                hours = value;
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
        /// Gets or sets the number of seconds (including the decimal portion)
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
        /// Returns a new instance of <see cref="T:RightAscension"/> by parsing <paramref name="rightAscensionString"/>.
        /// </summary>
        /// <param name="rightAscensionString">A string representing a right ascension.</param>
        /// <returns>A new instance of <see cref="T:Declination"/> by parsing <paramref name="rightAscensionString"/>.</returns>
        /// <remarks><paramref name="rightAscensionString"/> must have a format of "HH MM SS.S" where
        /// HH is the hours, MM is the minutes, and SS.S is the seconds.</remarks>
        public static RightAscension Parse(string rightAscensionString)
        {
            RightAscension rightAscension = new RightAscension();
            rightAscension.Hours = Convert.ToInt32(rightAscensionString.Substring(0, 3));
            rightAscension.Minutes = Convert.ToInt32(rightAscensionString.Substring(3, 3));
            rightAscension.Seconds = Convert.ToSingle(rightAscensionString.Substring(6));
            return rightAscension;
        }
    }
}
