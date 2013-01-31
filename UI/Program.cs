using System;
using System.Collections.Generic;
using System.Windows.Forms;
using ConstellationStation.UI;
using ConstellationStation.Graphics;
using ConstellationStation.Data;
using System.Threading;

namespace ConstellationStation.UI
{
    /// <summary>
    /// Entry point for the program.
    /// </summary>
    public class Program
    {
        // Fields
        /// <summary>
        /// A reference to the main form UI.
        /// </summary>
        private MainForm mainForm;
        /// <summary>
        /// A reference to the keyboard input controller.
        /// </summary>
        private KeyboardInputController keyboardInput;
        /// <summary>
        /// A reference to the mouse input controller.
        /// </summary>
        private MouseInputController mouseInput;
        /// <summary>
        /// A reference to the graphics controller.
        /// </summary>
        private GraphicsController graphics;
        /// <summary>
        /// A reference to the universe data store.
        /// </summary>
        private Universe universe;
        /// <summary>
        /// Whether or not the program is paused.
        /// </summary>
        private bool paused;

        // Constructors
        /// <summary>
        /// Constructs a new instance of the <see cref="T:Program"/> class.
        /// </summary>
        private Program()
        {
            universe = new Universe();
            mainForm = new MainForm();
            keyboardInput = new KeyboardInputController(universe);
            mouseInput = new MouseInputController(universe);
            graphics = new GraphicsController();
        }

        // Properties
        /// <summary>
        /// Gets a value indicating whether or not the program is paused.
        /// As long as the program is paused, no calls to the controllers are made.
        /// </summary>
        public bool IsPaused
        {
            get
            {
                return paused;
            }
        }

        // Methods
        /// <summary>
        /// Initialize the UI, graphics, and data controllers.
        /// </summary>
        private void Initialize()
        {
            // Initialize Data
            universe.NewUniverse();

            // Initialize UI
            mainForm.Program = this;
            mainForm.KeyboardInput = keyboardInput;
            mainForm.MouseInput = mouseInput;
            mainForm.Graphics = graphics;
            mainForm.Universe = universe;

            // Initialize Graphics
            graphics.InitializeGraphics(mainForm, universe);
        }
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        public static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Program program = new Program();
            program.Initialize();
            program.Run();
        }
        /// <summary>
        /// Pauses the program. See <see cref="P:IsPaused"/>.
        /// </summary>
        internal void Pause()
        {
            paused = true;
        }
        /// <summary>
        /// Resumes the program. See <see cref="P:IsPaused"/>.
        /// </summary>
        internal void Resume()
        {
            paused = false;
        }
        /// <summary>
        /// The main program loop.
        /// </summary>
        private void Run()
        {
            mainForm.Show();

            // Main program loop
            int ticksPrev = 0;
            int ticks = Environment.TickCount;
            while (mainForm.Created)
            {
                if (paused)
                {
                    Thread.Sleep(100);
                }
                else
                {
                    // Compute time elapsed
                    ticksPrev = ticks;
                    ticks = Environment.TickCount;
                    int ticksElapsed = ticks - ticksPrev;

                    // Handle input
                    keyboardInput.HandleInput(ticksElapsed);
                    mouseInput.HandleInput(ticksElapsed);

                    if (graphics.IsGraphicsInitialized)
                    {
                        // Render the graphics
                        graphics.RenderScene(ticksElapsed);
                    }
                }

                // Process events to keep the app from freezing
                Application.DoEvents();
            }
        }
    }
}