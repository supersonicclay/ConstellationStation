
using ConstellationStation.Common;
namespace ConstellationStation.Data
{
    /// <summary>
    /// Representation of a star.
    /// </summary>
    public class Star
    {
        // Properties
        /// <summary>
        /// Gets or sets the aparent magnitude of this star.
        /// </summary>
        public float AparentMagnitude { get; internal set; }
        /// <summary>
        /// Gets or sets the equitorial coordinates (right ascension and declination) of this star.
        /// </summary>
        public EquitorialCoordinates EquitorialCoordinates { get; internal set; }
        /// <summary>
        /// Gets or sets the Hipparcos catalog identifier for this star.
        /// </summary>
        public int HipparcosId { get; internal set; }
        /// <summary>
        /// Gets or sets the common name of this star.
        /// </summary>
        public string Name { get; internal set; }
        /// <summary>
        /// Gets or sets the spectral type of this star.
        /// </summary>
        public Spectral.SpectralType SpectralType { get; internal set; }
    }
}
