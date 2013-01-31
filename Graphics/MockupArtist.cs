using System;
using System.Drawing;
using ConstellationStation.Data;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace ConstellationStation.Graphics
{
    /// <summary>
    /// Draws mockup objects and textures used for testing.
    /// </summary>
    public class MockupArtist : Artist
    {
        // Fields
        /// <summary>
        /// A texture of a star.
        /// </summary>
        private Texture starTexture = null;

        // Properties
        /// <summary>
        /// Gets a value indicating if this <see cref="T:MockupArtist"/> is initialized and ready for use.
        /// </summary>
        public override bool IsInitialized
        {
            get { return starTexture != null; }
        }

        // Methods
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
        }
        /// <summary>
        /// Loads the textures needed by this <see cref="T:MockupArtist"/>.
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
        /// Render the components for which this artist is responsible.
        /// </summary>
        /// <param name="ticksElapsed">The number of ticks elapsed since this method was last called</param>
        public override void Render(int ticksElapsed)
        {
            Device.SetTexture(0, null);
            CustomVertex.TransformedColored[] verts2 = new CustomVertex.TransformedColored[3];
            verts2[0].X = 150; verts2[0].Y = 50; verts2[0].Z = 0.5f; verts2[0].Rhw = 1; verts2[0].Color = System.Drawing.Color.Red.ToArgb();
            verts2[1].X = 250; verts2[1].Y = 250; verts2[1].Z = 0.5f; verts2[1].Rhw = 1; verts2[1].Color = System.Drawing.Color.Blue.ToArgb();
            verts2[2].X = 50; verts2[2].Y = 250; verts2[2].Z = 0.5f; verts2[2].Rhw = 1; verts2[2].Color = System.Drawing.Color.Yellow.ToArgb();
            Device.VertexFormat = CustomVertex.TransformedColored.Format;
            Device.DrawUserPrimitives(PrimitiveType.TriangleList, 1, verts2);

            
            Device.SetTexture(0, starTexture);
            StarVertex[] verts = new StarVertex[4];
            verts[0] = new StarVertex()
            {
                Position = new Vector3(-0.2f, 0.1f, 1.0f),
                PointSize = 0.5f,
                Color = Color.White.ToArgb()
            };
            verts[1] = new StarVertex()
            {
                Position = new Vector3(-0.2f, -0.1f, 1.0f),
                PointSize = 0.5f,
                Color = Color.FromArgb(10, Color.White).ToArgb()
            };
            verts[2] = new StarVertex()
            {
                Position = new Vector3(0.16f, 0.0f, 1.0f),
                PointSize = 0.1f,
                Color = Color.White.ToArgb()
            };
            verts[3] = new StarVertex()
            {
                Position = new Vector3(0.2f, 0.0f, 1.0f),
                PointSize = 0.2f,
                Color = Color.White.ToArgb()
            };

            Device.VertexFormat = StarVertex.Format;
            Device.DrawUserPrimitives(PrimitiveType.PointList, verts.Length, verts);

        }
    }
}
