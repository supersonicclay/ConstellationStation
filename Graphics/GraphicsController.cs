using System;
using System.Drawing;
using System.Windows.Forms;
using ConstellationStation.Data;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace ConstellationStation.Graphics
{
    /// <summary>
    /// Container and controller of all artists.
    /// </summary>
    public class GraphicsController
    {
        // Fields
        /// <summary>
        /// The debugging artist.
        /// </summary>
        private DebugArtist debugArtist = null;
        /// <summary>
        /// The DirectX device.
        /// </summary>
        private Device device = null;
        /// <summary>
        /// The main Windows form.
        /// </summary>
        private Form form = null;
        /// <summary>
        /// The frames-per-second counter.
        /// </summary>
        private FpsCounter fpsCounter = null;
        /// <summary>
        /// The mockup artist.
        /// </summary>
        private MockupArtist mockupArtist = null;
        /// <summary>
        /// The starfield artist.
        /// </summary>
        private StarfieldArtist starfieldArtist = null;
        /// <summary>
        /// The universe.
        /// </summary>
        private Universe universe = null;

        // Properties
        /// <summary>
        /// Gets a value indicating if this <see cref="T:GraphicsMain"/> is initialized and ready for use.
        /// </summary>
        public bool IsGraphicsInitialized
        {
            get { return device != null; }
        }
        /// <summary>
        /// Gets the artist responsible for drawing debugging information.
        /// </summary>
        public DebugArtist DebugArtist
        {
            get { return debugArtist; }
        }
        /// <summary>
        /// Gets the artist responsible for drawing the mockup.
        /// </summary>
        public MockupArtist MockupArtist
        {
            get { return mockupArtist; }
        }
        /// <summary>
        /// Gets the artist responsible for drawing the starfield.
        /// </summary>
        public StarfieldArtist StarfieldArtist
        {
            get { return starfieldArtist; }
        }

        // Methods
        /// <summary>
        /// Initializes all artists.
        /// </summary>
        private void InitializeArtists()
        {
            debugArtist.Initialize(device, universe);
            mockupArtist.Initialize(device, universe);
            starfieldArtist.Initialize(device, universe);
        }
        /// <summary>
        /// Initialize properties of the device, such as render state and default transform matrix.
        /// </summary>
        private void InitializeDevice()
        {
            device.RenderState.Lighting = false;

            device.RenderState.AlphaBlendEnable = true;
            device.RenderState.SourceBlend = Blend.One;
            device.RenderState.DestinationBlend = Blend.One;

            device.RenderState.PointSpriteEnable = true;
            device.RenderState.PointScaleEnable = true;
            device.RenderState.PointScaleA = 1.0f;
            device.RenderState.PointScaleB = 0.0f;
            device.RenderState.PointScaleC = 0.0f;

            device.Transform.Projection = Matrix.PerspectiveFovLH((float)System.Math.PI / 4, (float)form.ClientRectangle.Width / form.ClientRectangle.Height, 0.1f, 100.0f);
        }
        /// <summary>
        /// Initializes the graphics system and all artists.
        /// </summary>
        /// <param name="form">The Windows form representing the GUI window.</param>
        /// <param name="universe">A <see cref="T:Universe"/> representing the data.</param>
        public void InitializeGraphics(Form form, Universe universe)
        {
            try
            {
                this.universe = universe;
                this.form = form;

                PresentParameters pps = new PresentParameters();
                pps.Windowed = true;    // Specify that it will be in a window
                pps.SwapEffect = SwapEffect.Discard;    // After the current screen is drawn, it will be automatically deleted from memory
                device = new Device(0, DeviceType.Hardware, form, CreateFlags.SoftwareVertexProcessing, pps); // Put everything into the device
                device.DeviceReset += OnDeviceReset;

                debugArtist = new DebugArtist();
                mockupArtist = new MockupArtist();
                starfieldArtist = new StarfieldArtist();
                fpsCounter = new FpsCounter();

                InitializeDevice();
                InitializeArtists();
            }
            catch (DirectXException e)
            {
                Console.WriteLine(e.Message);
                Console.WriteLine(e.StackTrace);
                throw new Exception("Error initializing DirectX");
            }
        }
        /// <summary>
        /// Handle the device reset event.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:EventArgs"/>.</param>
        private void OnDeviceReset(object sender, EventArgs e)
        {
            DebugArtist.AddLogMessage("Device reset");
            InitializeDevice();
            InitializeArtists();
        }
        /// <summary>
        /// Render the graphics scene.
        /// </summary>
        /// <param name="timeElapsed">The amount of time elapsed, in ticks,
        /// since <see cref="M:RenderScene(int)"/> was last called.</param>
        public void RenderScene(int timeElapsed)
        {
            if (device == null)
            {
                throw new Exception("Graphics are not initialized");
            }
            device.Clear(ClearFlags.Target, Color.Black, 1.0f, 0);
            device.BeginScene();

            if (universe.ShowMockup)
            {
                mockupArtist.Render(timeElapsed);
            }
            starfieldArtist.Render(timeElapsed);

            if (universe.ShowDebug)
            {
                debugArtist.Render(timeElapsed);
            }

            DebugArtist.AddRealtimeMessageLine("FPS: " + fpsCounter.CalculateFPS());

            device.EndScene();
            device.Present();
        }
    }
}
