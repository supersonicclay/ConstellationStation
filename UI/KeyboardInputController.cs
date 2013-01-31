using System;
using System.Collections.Generic;
using System.Text;
using ConstellationStation.Graphics;
using ConstellationStation.Data;
using System.Windows.Forms;

namespace ConstellationStation.UI
{
    /// <summary>
    /// Responsible for handling keyboard events and taking appropriate action.
    /// </summary>
    public class KeyboardInputController
    {
        // Constants
        /// <summary>
        /// The multiplier used for the speed of keyboard rotation.
        /// </summary>
        private const float KeyboardRotationMultiplier = 0.0005f;
        /// <summary>
        /// The mutiplier used for the speed of keyboard zoom.
        /// </summary>
        private const float KeyboardZoomMultiplier = 0.0002f;

        // Fields
        /// <summary>
        /// Whether or not the user is in the process of rotating down.
        /// </summary>
        private bool rotateDown;
        /// <summary>
        /// Whether or not the user is in the process of rotating left.
        /// </summary>
        private bool rotateLeft;
        /// <summary>
        /// Whether or not the user is in the process of rotating right.
        /// </summary>
        private bool rotateRight;
        /// <summary>
        /// Whether or not the user is in the process of rotating up.
        /// </summary>
        private bool rotateUp;
        /// <summary>
        /// A reference to the universe for accessing data.
        /// </summary>
        private Universe universe;
        /// <summary>
        /// Whether or not the user is in the process of zooming in.
        /// </summary>
        private bool zoomIn;
        /// <summary>
        /// Whether or not the user is in the process of zooming out.
        /// </summary>
        private bool zoomOut;

        // Constructors
        /// <summary>
        /// Constructs a new instance of the <see cref="T:KeyboardInputController"/> class.
        /// </summary>
        /// <param name="universe">A reference to the universe.</param>
        /// <exception cref="T:ArgumentNullException"><paramref name="universe"/> is null.</exception>
        public KeyboardInputController(Universe universe)
        {
            if (universe == null)
            {
                throw new ArgumentNullException("universe");
            }
            this.universe = universe;
        }

        // Methods
        /// <summary>
        /// Called continuously, handles the input that's been recorded with other event handlers.
        /// </summary>
        /// <param name="timeElapsed">The number of ticks elapsed since this method was last called.</param>
        public void HandleInput(int ticksElapsed)
        {
            if (rotateUp)
            {
                universe.Navigation.AdjustXRotation(ticksElapsed * KeyboardRotationMultiplier);
            }
            if (rotateDown)
            {
                universe.Navigation.AdjustXRotation(-ticksElapsed * KeyboardRotationMultiplier);
            }
            if (rotateLeft)
            {
                universe.Navigation.AdjustYRotation(ticksElapsed * KeyboardRotationMultiplier);
            }
            if (rotateRight)
            {
                universe.Navigation.AdjustYRotation(-ticksElapsed * KeyboardRotationMultiplier);
            }
            if (zoomIn)
            {
                universe.Navigation.Zoom += ticksElapsed * KeyboardZoomMultiplier;
            }
            if (zoomOut)
            {
                universe.Navigation.Zoom -= ticksElapsed * KeyboardZoomMultiplier;
            }

            DebugArtist.AddRealtimeMessageLine("XRotation: " + universe.Navigation.XRotation + "  YRotation: " + universe.Navigation.YRotation + "  Zoom: " + universe.Navigation.Zoom);
        }
        /// <summary>
        /// A key was pressed down.
        /// </summary>
        /// <param name="e">A <see cref="T:KeyEventArgs"/> describing the key pressed down.</param>
        public void KeyDown(KeyEventArgs e)
        {
            ToggleKey(e, true);
        }
        /// <summary>
        /// Key was pressed down and released.
        /// </summary>
        /// <param name="e">A <see cref="T:KeyPressEventArgs"/> describing the key pressed.</param>
        public void KeyPress(KeyPressEventArgs e)
        {
            switch (e.KeyChar)
            {
                case '\r':
                case '\n':
                    universe.Navigation.XRotation = 0.0f;
                    universe.Navigation.YRotation = 0.0f;
                    break;
                case 'M':
                case 'm':
                    universe.ShowMockup = !universe.ShowMockup;
                    break;
                case ' ':
                    universe.ShowDebug = !universe.ShowDebug;
                    break;
                default:
                    break;
            }
        }
        /// <summary>
        /// A key was released.
        /// </summary>
        /// <param name="e">A <see cref="T:KeyEventArgs"/> describing the key released.</param>
        public void KeyUp(KeyEventArgs e)
        {
            ToggleKey(e, false);
        }
        /// <summary>
        /// Toggles whether or not the key described by <paramref name="e"/> is pressed.
        /// </summary>
        /// <param name="e">An <see cref="T:KeyEventArgs"/> describing the key pressed or released.</param>
        /// <param name="keyDown"><c>true</c> if the key is depressed; <c>false</c> if the key is released.</param>
        private void ToggleKey(KeyEventArgs e, bool keyDown)
        {
            switch (e.KeyCode)
            {
                case Keys.Up:
                    rotateUp = keyDown;
                    break;
                case Keys.Down:
                    rotateDown = keyDown;
                    break;
                case Keys.Left:
                    rotateLeft = keyDown;
                    break;
                case Keys.Right:
                    rotateRight = keyDown;
                    break;
                case Keys.Add:
                    zoomIn = keyDown;
                    break;
                case Keys.Subtract:
                    zoomOut = keyDown;
                    break;
                default:
                    break;
            }
            switch (e.KeyValue)
            {
                case 187:
                    zoomIn = keyDown;
                    break;
                case 189:
                    zoomOut = keyDown;
                    break;
                default:
                    break;
            }
        }
    }
}
