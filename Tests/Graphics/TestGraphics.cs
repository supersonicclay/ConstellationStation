using System.Drawing;
using ConstellationStation.Data;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using NUnit.Framework;
using System.Windows.Forms;

namespace ConstellationStation.Graphics
{
    [TestFixture]
    public class TestGraphics
    {
        private const float DELTA = 0.01f;

        Form form;
        Universe universe;
        GraphicsController graphics;

        [TestFixtureSetUp]
        public void InitializeGraphics()
        {
            universe = new Universe();
            universe.NewUniverse();
            form = new Form();
            graphics = new GraphicsController();
            graphics.InitializeGraphics(form, universe);
        }

        [Test]
        public void GraphicsInitialized()
        {
            Assert.IsTrue(graphics.IsGraphicsInitialized);
        }

        [Test]
        public void MockupArtistInitialized()
        {
            Assert.IsTrue(graphics.MockupArtist.IsInitialized);
        }

        [Test]
        public void StarfieldArtistInitialized()
        {
            Assert.IsTrue(graphics.StarfieldArtist.IsInitialized);
        }

        [Test]
        public void DebugArtistInitialized()
        {
            Assert.IsTrue(graphics.DebugArtist.IsInitialized);
        }

        [Test]
        public void StarsBuffer()
        {
            try
            {
                StarVertex[] starVertices = (StarVertex[])graphics.StarfieldArtist.StarsBuffer.Lock(0, LockFlags.None);
                Assert.AreEqual(Starfield.SectorSubdivisionsRightAscension * Starfield.SectorSubdivisionsDeclination * Starfield.MaximumStarsPerSector, starVertices.Length);

                // Get the vertex index for Vega
                const int VEGA_SECTOR_RA = 15; // right ascension sector
                const int VEGA_SECTOR_DEC = 7; // declination sector
                const int VEGA_STAR_INDEX = 0; // index into that sector
                int vertexIndex = StarfieldArtist.GetArrayIndexForSector(VEGA_SECTOR_RA, VEGA_SECTOR_DEC) + VEGA_STAR_INDEX;

                // Assert position is correct for Vega
                StarVertex vegaVertex = starVertices[vertexIndex];
                AssertX.AreEqual(new Vector3(0.769421875f, 0.626372576f, 0.125089318f), vegaVertex.Position, DELTA);
            }
            finally
            {
                graphics.StarfieldArtist.StarsBuffer.Unlock();
            }
        }

        [Test]
        public void GetPointSizeForMagnitude()
        {
            // Brightest
            Assert.AreEqual(StarfieldArtist.BrightestRadius, StarfieldArtist.GetRadiusForMagnitude(Starfield.BrightestMagnitude), DELTA);

            // Dimmest
            Assert.AreEqual(StarfieldArtist.DimmestRadius, StarfieldArtist.GetRadiusForMagnitude(Starfield.DimmestMagnitude), DELTA);

            // Half way
            float radius, magnitude;
            radius = (StarfieldArtist.BrightestRadius - StarfieldArtist.DimmestRadius) / 2 + StarfieldArtist.DimmestRadius;
            magnitude = -1 * (Starfield.BrightestMagnitude - Starfield.DimmestMagnitude) / 2 + Starfield.BrightestMagnitude;
            Assert.AreEqual(radius, StarfieldArtist.GetRadiusForMagnitude(magnitude), DELTA);
        }

        [Test]
        public void TestGetColorForMagnitude()
        {
            // Brightest
            Assert.AreEqual(Color.FromArgb(255, Color.White), StarfieldArtist.GetColorForMagnitude(Starfield.BrightestMagnitude));

            // Dimmest
            Assert.AreEqual(Color.FromArgb(0, Color.White), StarfieldArtist.GetColorForMagnitude(Starfield.DimmestMagnitude));

            // Half way
            float magnitude = -1 * (Starfield.BrightestMagnitude - Starfield.DimmestMagnitude) / 2 + Starfield.BrightestMagnitude;
            Color color = Color.FromArgb(127, Color.White);
            Assert.AreEqual(color, StarfieldArtist.GetColorForMagnitude(magnitude));
        }
    }
}
