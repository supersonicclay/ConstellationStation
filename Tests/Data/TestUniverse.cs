using System.Collections.Generic;
using ConstellationStation.Common;
using NUnit.Framework;

namespace ConstellationStation.Data
{
    [TestFixture]
    public class TestUniverse
    {
        private const float DELTA = 0.01f;
        private const int STAR_COUNT = 83392;

        Universe universe;

        [TestFixtureSetUp]
        public void InitializeUniverse()
        {
            universe = new Universe();
            universe.NewUniverse();
        }


        [Test]
        public void UniverseCreated()
        {
            Assert.IsNotNull(universe.Navigation);
            Assert.IsNotNull(universe.Starfield);
        }

        [Test]
        public void StarfieldCreated()
        {
            Assert.IsNotNull(universe.Starfield.Stars);
            Assert.AreEqual(STAR_COUNT, universe.Starfield.Stars.Count);
        }

        [Test]
        public void VegaCreated()
        {
            Star vega = universe.Starfield.Stars[91262];
            Assert.IsNotNull(vega);

            // Hipparcos id
            Assert.AreEqual(91262, vega.HipparcosId);

            // Right Ascension
            AssertX.AreEqual(new RightAscension() { Hours = 18, Minutes = 36, Seconds = 56.19f }, vega.EquitorialCoordinates.RightAscension, DELTA);

            // Declination
            AssertX.AreEqual(new Declination() { Positive = true, Degrees = 38, Minutes = 46, Seconds = 58.8f }, vega.EquitorialCoordinates.Declination, DELTA);

            // Magnitude
            Assert.AreEqual(0.03f, vega.AparentMagnitude, DELTA);

            // Spectral type
            Assert.AreEqual(Spectral.SpectralType.A, vega.SpectralType);

            // Name
            Assert.AreEqual("Vega", vega.Name);
        }

        [Test]
        public void RigelCreated()
        {
            Star rigel = universe.Starfield.Stars[24436];
            Assert.IsNotNull(rigel);

            // Hipparcos id
            Assert.AreEqual(24436, rigel.HipparcosId);

            // Right Ascension
            AssertX.AreEqual(new RightAscension() { Hours = 5, Minutes = 14, Seconds = 32.27f }, rigel.EquitorialCoordinates.RightAscension, DELTA);

            // Declination
            AssertX.AreEqual(new Declination() { Positive = false, Degrees = 8, Minutes = 12, Seconds = 5.9f }, rigel.EquitorialCoordinates.Declination, DELTA);

            // Magnitude
            Assert.AreEqual(0.18f, rigel.AparentMagnitude, DELTA);

            // Spectral type
            Assert.AreEqual(Spectral.SpectralType.B, rigel.SpectralType);

            // Name
            Assert.AreEqual("Rigel", rigel.Name);
        }

        [Test]
        public void StarSectorsFilled()
        {
            int? max = null;
            int? min = null;
            int count = 0;
            Assert.AreEqual(Starfield.SectorSubdivisionsRightAscension * Starfield.SectorSubdivisionsDeclination, universe.Starfield.StarSectors.Length);
            foreach (List<Star> sector in universe.Starfield.StarSectors)
            {
                count += sector.Count;
                if (sector.Count > max || max == null)
                {
                    max = sector.Count;
                }
                if (sector.Count < min || min == null)
                {
                    min = sector.Count;
                }
            }

            Assert.Greater(min, 0);
            Assert.LessOrEqual(max, Starfield.MaximumStarsPerSector);
            Assert.AreEqual(STAR_COUNT, count);
        }
    }
}
