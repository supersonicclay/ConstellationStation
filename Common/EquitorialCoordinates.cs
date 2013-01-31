
namespace ConstellationStation.Common
{
    /// <summary>
    /// Represents a set of equitorial coordinates (right ascension and declination).
    /// </summary>
    public struct EquitorialCoordinates
    {
        // Fields
        /// <summary>
        /// The declination portion of the coordinate.
        /// </summary>
        public Declination Declination;
        /// <summary>
        /// The right ascension portion of the coordinate.
        /// </summary>
        public RightAscension RightAscension;
    }
}
