using System;
using System.Drawing;
using ConstellationStation.Common;
using ConstellationStation.Data;
using ConstellationStation.Math;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace ConstellationStation.Graphics
{
    /// <summary>
    /// Renders the starfield in 3d.
    /// </summary>
    public class StarfieldArtist : Artist
    {
        // Constants
        /// <summary>
        /// The radius of the brightest star.
        /// </summary>
        public const float BrightestRadius = 0.04f;
        /// <summary>
        /// The radius of the dimmest star.
        /// </summary>
        public const float DimmestRadius = 0.001f;

        // Fields
        /// <summary>
        /// Array of bounding spheres, one for each sector.
        /// </summary>
        private BoundingSphere[][] boundingSpheres = null;
        /// <summary>
        /// Vertex buffers for all stars.
        /// </summary>
        private VertexBuffer starsBuffer = null;
        /// <summary>
        /// A texture of a star.
        /// </summary>
        private Texture starTexture = null;

        // Properties
        /// <summary>
        /// Gets a value indicating if this <see cref="T:Artist"/> is initialized and ready for use.
        /// </summary>
        public override bool IsInitialized
        {
            get
            {
                return starTexture != null && starsBuffer != null;
            }
        }
        /// <summary>
        /// Gets the vertex buffer for all stars.
        /// </summary>
        public VertexBuffer StarsBuffer
        {
            get { return starsBuffer; }
        }

        // Methods
        /// <summary>
        /// Construct the bounding spheres array.
        /// </summary>
        private void ConstructBoundingSpheres()
        {
            boundingSpheres = new BoundingSphere[Starfield.SectorSubdivisionsRightAscension][];
            for (int i = 0; i < Starfield.SectorSubdivisionsRightAscension; ++i)
            {
                boundingSpheres[i] = new BoundingSphere[Starfield.SectorSubdivisionsDeclination];
            }
        }
        /// <summary>
        /// Fill the star vertex buffer. Stars are stored in two-dimensional array in 
        /// <see cref="T:Starfield"/>, but place them in a single <see cref="T:VertexBuffer"/>.
        /// </summary>
        /// <param name="starsBuffer">The <see cref="T:VertexBuffer"/> to contain the star vertices.</param>
        private void CreateStarsBuffer(VertexBuffer starsBuffer)
        {
            StarVertex[] starVerts = (StarVertex[])starsBuffer.Lock(0, 0);

            for (int i = 0; i < Starfield.SectorSubdivisionsRightAscension; ++i)
            {
                for (int j = 0; j < Starfield.SectorSubdivisionsDeclination; ++j)
                {
                    // Start index into the vertex array
                    int startIndex = GetArrayIndexForSector(i, j);

                    int starCount = 0;
                    foreach (Star star in Universe.Starfield.StarSectors[i,j])
                    {
                        // Get x, y, z coordinates
                        SphericalCoordinates spherical;
                        Angles.SphericalFromEquatorial(out spherical, star.EquitorialCoordinates);
                        Vector3 position;
                        Angles.Vector3FromSpherical(out position, spherical);

                        // Get point size
                        float pointSize = GetRadiusForMagnitude(star.AparentMagnitude);

                        // Get color
                        int color = GetColorForMagnitude(star.AparentMagnitude).ToArgb();

                        // Get the index into the buffer
                        int vertIndex = startIndex + starCount;

                        // Add the vertex to the buffer
                        starVerts[vertIndex] = new StarVertex()
                        {
                            Position = position,
                            PointSize = pointSize,
                            Color = color
                        };
                        starCount++;
                    }

                    // Copy this portion of the vertex buffer to a temp array to compute bounding sphere
                    StarVertex[] sectorVertices = new StarVertex[starCount];
                    Array.Copy(starVerts, startIndex, sectorVertices, 0, starCount);

                    // Compute bounding sphere for this sector
                    BoundingSphere bs = new BoundingSphere();
                    bs.Radius = Geometry.ComputeBoundingSphere(sectorVertices, StarVertex.Format, out bs.Center);
                    boundingSpheres[i][j] = bs;
                }
            }

            starsBuffer.Unlock();
        }
        /// <summary>
        /// Get the index into the vertex buffer array for the first vertex of the given sector.
        /// </summary>
        /// <param name="indexRA">Horizontal array index (i.e. right ascension).</param>
        /// <param name="indexDEC">Verticle array index (i.e. declination).</param>
        /// <returns></returns>
        public static int GetArrayIndexForSector(int indexRightAscension, int indexDeclination)
        {
            return
                indexRightAscension * Starfield.MaximumStarsPerSector * Starfield.SectorSubdivisionsDeclination +
                indexDeclination * Starfield.MaximumStarsPerSector;
        }
        /// <summary>
        /// Returns a color (including alpha) corresponding to <paramref name="aparentMagnitude"/>.
        /// </summary>
        /// <param name="aparentMagnitude">The aparent magnitude.</param>
        /// <returns>A color (including alpha) corresponding to <paramref name="aparentMagnitude"/>.</returns>
        public static Color GetColorForMagnitude(float aparentMagnitude)
        {
            float magnitudeRange = -1 * (Starfield.BrightestMagnitude - Starfield.DimmestMagnitude); // multiply by -1 because brighter magnitude is lower

            // Multiplier in the range of 0 to 1 based on given magnitude
            float multiplier = -1 * (aparentMagnitude - Starfield.DimmestMagnitude) / magnitudeRange;

            int alpha = (int)(255 * multiplier);

            return Color.FromArgb(alpha, Color.White);
        }
        /// <summary>
        /// Returns a point size corresponding to <paramref name="aparentMagnitude"/>.
        /// </summary>
        /// <param name="aparentMagnitude">The aparent magnitude.</param>
        /// <returns>A point size corresponding to <paramref name="aparentMagnitude"/>.</returns>
        public static float GetRadiusForMagnitude(float aparentMagnitude)
        {
            float magnitudeRange = -1 * (Starfield.BrightestMagnitude - Starfield.DimmestMagnitude); // multiply by -1 because brighter magnitude is lower
            float radiusRange = StarfieldArtist.BrightestRadius - StarfieldArtist.DimmestRadius;

            // Multiplier in the range of 0 to 1 based on given magnitude
            float multiplier = -1 * (aparentMagnitude - Starfield.DimmestMagnitude) / magnitudeRange;

            return (multiplier * radiusRange) + StarfieldArtist.DimmestRadius;
        }
        /// <summary>
        /// Initializes this artist. This is called
        /// when the program is first started and also when the device is reset.
        /// </summary>
        protected override void InitializeArtist()
        {
            if (starTexture == null)
            {
                LoadTextures();
            }
            if (boundingSpheres == null)
            {
                ConstructBoundingSpheres();
            }
            if (starsBuffer == null)
            {
                InitializeStarsBuffer();
            }
        }
        /// <summary>
        /// Create the stars buffer.
        /// </summary>
        private void InitializeStarsBuffer()
        {
            int vertexCount = Starfield.MaximumStarsPerSector * Starfield.SectorSubdivisionsRightAscension * Starfield.SectorSubdivisionsDeclination;
            starsBuffer = new VertexBuffer(typeof(StarVertex), vertexCount, Device, 0, StarVertex.Format, Pool.Default);
            starsBuffer.Created += OnCreateStarsBuffer;
            CreateStarsBuffer(starsBuffer);
        }
        /// <summary>
        /// Loads the textures needed for this <see cref="T:StarfieldArtist"/>.
        /// </summary>
        private void LoadTextures()
        {
            try
            {
                starTexture = TextureLoader.FromFile(Device, DataResources.StarTexture);
            }
            catch (DirectXException e)
            {
                Console.WriteLine(e.ToString());
                throw new Exception("Error loading textures");
            }
        }
        /// <summary>
        /// Handle the created event for the vertex buffer so that it can be refilled.
        /// </summary>
        /// <param name="sender">The sender of the event (the <see cref="T:VertexBuffer"/>.</param>
        /// <param name="e">The <see cref="T:EventArgs"/>.</param>
        private void OnCreateStarsBuffer(object sender, EventArgs e)
        {
            VertexBuffer vb = (VertexBuffer)sender;
            CreateStarsBuffer(vb);
        }
        /// <summary>
        /// Render the components for which this artist is responsible.
        /// </summary>
        /// <param name="ticksElapsed">The number of ticks elapsed since this method was last called</param>
        public override void Render(int ticksElapsed)
        {
            Matrix viewMatBefore = Device.Transform.View;

            // Apply view rotations
            Device.Transform.View = Matrix.RotationY(Universe.Navigation.YRotation) * Matrix.RotationX(Universe.Navigation.XRotation);
            Frustum frustum = Frustum.FromViewProjMatrices(Device.Transform.View, Device.Transform.Projection);

            // Apply zoom
            float fov = Interpolations.Lerp(Universe.Navigation.Zoom, (float)System.Math.PI / 4, (float)System.Math.PI / 32);
            float aspect = 1.0f;// (float)mainForm.ClientRectangle.Width / mainForm.ClientRectangle.Height;
            Device.Transform.Projection = Matrix.PerspectiveFovLH(fov, aspect, 0.1f, 100.0f);

            // Set star texture
            Device.SetTexture(0, starTexture);

            // Draw stars
            Device.VertexFormat = StarVertex.Format;
            Device.SetStreamSource(0, starsBuffer, 0);
            for (int i = 0; i < Starfield.SectorSubdivisionsRightAscension; ++i)
            {
                for (int j = 0; j < Starfield.SectorSubdivisionsDeclination; ++j)
                {
                    if (frustum.ContainsSphere(boundingSpheres[i][j]))
                    {
                        int startIndex = GetArrayIndexForSector(i, j);
                        Device.DrawPrimitives(PrimitiveType.PointList, startIndex, Universe.Starfield.StarSectors[i,j].Count);
                    }
                }
            }

            Device.Transform.View = viewMatBefore;
        }
    }
}
