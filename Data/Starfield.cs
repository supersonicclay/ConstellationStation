using System;
using System.Collections.Generic;
using System.IO;
using ConstellationStation.Common;

namespace ConstellationStation.Data
{
    /// <summary>
    /// Representation of a starfield, that is a collection of celestial objects.
    /// </summary>
    public class Starfield
    {
        // Constants
        /// <summary>
        /// The brightest apparent magnitude of all the stars.
        /// </summary>
        public const float BrightestMagnitude = -1.44f;
        /// <summary>
        /// The dimmest apparent magnitude of all the stars.
        /// </summary>
        public const float DimmestMagnitude = 9.00f;
        /// <summary>
        /// The maximum number of stars in each star sector.
        /// </summary>
        public const int MaximumStarsPerSector = 1400;
        /// <summary>
        /// The number of horizontal subdivisions used for the star sectors.
        /// </summary>
        public const int SectorSubdivisionsRightAscension = 20;
        /// <summary>
        /// The number of vertical subdivisions used for the star sectors.
        /// </summary>
        public const int SectorSubdivisionsDeclination = 10;

        // Fields
        /// <summary>
        /// Backing store for the stars.
        /// </summary>
        private Dictionary<int, Star> stars;
        /// <summary>
        /// Backing store for the star sectors.
        /// </summary>
        private ICollection<Star>[,] starSectors;

        // Properties
        /// <summary>
        /// Gets a <see cref="T:Dictionary"/> of hipparcos ids to <see cref="T:Star"/> objects.
        /// </summary>
        public Dictionary<int, Star> Stars
        {
            get { return stars; }
        }
        /// <summary>
        /// Gets a grid of star sectors. A star sector is a segment of the celestial sphere
        /// containing an <see cref="T:ICollection"/> of stars.
        /// </summary>
        public ICollection<Star>[,] StarSectors
        {
            get { return starSectors; }
        }

        // Methods
        /// <summary>
        /// Initializes this <see cref="T:Starfield"/> with new stars.
        /// </summary>
        internal void NewStarfield()
        {
            stars = new Dictionary<int, Star>();
            starSectors = new List<Star>[SectorSubdivisionsRightAscension,SectorSubdivisionsDeclination];
            for (int i=0; i<SectorSubdivisionsRightAscension; ++i)
            {
                for (int j = 0; j < SectorSubdivisionsDeclination; ++j)
                {
                    starSectors[i,j] = new List<Star>();
                }
            }

            LoadStars();
        }
        /// <summary>
        /// Reads stars from the star catalog and stores them in this <see cref="T:Starfield"/>.
        /// </summary>
        private void LoadStars()
        {
            using (StreamReader catalog = File.OpenText(DataResources.StarCatalog))
            {
                string entry;
                while (!string.IsNullOrEmpty(entry = catalog.ReadLine()))
                {
                    Star star = new Star();
                    EquitorialCoordinates equitorial = new EquitorialCoordinates();
                    
                    string hid = entry.Substring(0, 7);
                    star.HipparcosId = Convert.ToInt32(hid);

                    string ra = entry.Substring(7, 12);
                    equitorial.RightAscension = RightAscension.Parse(ra);

                    string dec = entry.Substring(19, 12);
                    equitorial.Declination = Declination.Parse(dec);
                    star.EquitorialCoordinates = equitorial;

                    string mag = entry.Substring(31, 7);
                    star.AparentMagnitude = Convert.ToSingle(mag);

                    string specType = entry.Substring(38, 2).Trim();
                    star.SpectralType = Spectral.Parse(specType);

                    string name = entry.Substring(40).Trim();
                    star.Name = name;

                    stars[star.HipparcosId] = star;
                    AddStarToSector(star);
                }
            }
        }
        /// <summary>
        /// Adds <paramref name="star"/> to the appropriate star sector
        /// based on its right ascension and declination.
        /// </summary>
        /// <param name="star">A star to add to a sector.</param>
        private void AddStarToSector(Star star)
        {
            int indexRA = GetSectorIndexForRightAscension(star.EquitorialCoordinates.RightAscension);
            int indexDEC = GetSectorIndexForDeclination(star.EquitorialCoordinates.Declination);
            starSectors[indexRA,indexDEC].Add(star);
        }
        /// <summary>
        /// Returns the horizontal star sector index based on <paramref name="rightAscension"/>.
        /// </summary>
        /// <param name="rightAscension">The right ascensions for which to get the horizontal star sector index.</param>
        /// <returns>The horizontal star sector index based on <paramref name="rightAscension"/>.</returns>
        public int GetSectorIndexForRightAscension(RightAscension rightAscension)
        {
            return rightAscension.Hours * SectorSubdivisionsRightAscension / 24;
        }
        /// <summary>
        /// Returns the vertical star sector index based on <paramref name="declination"/>.
        /// </summary>
        /// <param name="declination">The declination for which to get the vertical star sector index.</param>
        /// <returns>The vertical star sector index based on <paramref name="declination"/>.</returns>
        public int GetSectorIndexForDeclination(Declination declination)
        {
            // declination is [-90,90] degrees, transform to [0,180]
            int degrees = declination.Positive ? declination.Degrees : -declination.Degrees;
            
            return (degrees + 90) * SectorSubdivisionsDeclination / 180;
        }
    }
}
