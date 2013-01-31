using System;
using ConstellationStation.Data;
using System.Drawing;
using System.Windows.Forms;

namespace ConstellationStation.UI
{
    /// <summary>
    /// Responsible for handling mouse events and taking appropriate action.
    /// </summary>
    public class MouseInputController
    {
        // Constants
        /// <summary>
        /// The multiplier used for the speed of vertical mouse rotation.
        /// </summary>
        private const float MouseRotationVerticalMultiplier = 0.002f;
        /// <summary>
        /// The multiplier used for the speed of horizontal mouse rotation.
        /// </summary>
        private const float MouseRotationHorizontalMultiplier = 0.0015f;
        /// <summary>
        /// The multiplier used for the speed of mouse wheel zoom.
        /// </summary>
        private const float MouseWheelZoomMultiplier = 0.0005f;

        // Fields
        /// <summary>
        /// The point of the mouse cursor the last time a mouse event occured.
        /// </summary>
        private Point lastMouseLocation;
        /// <summary>
        /// Whether or not the user currently has the left mouse button pressed.
        /// </summary>
        private bool leftMouseButtonPressed;
        /// <summary>
        /// A reference to the universe for accessing data.
        /// </summary>
        private Universe universe;

        // Constructors
        /// <summary>
        /// Constructs a new instance of the <see cref="T:MouseInputController"/> class.
        /// </summary>
        /// <param name="universe">A reference to the universe.</param>
        /// <exception cref="T:ArgumentNullException"><paramref name="universe"/> is null.</exception>
        public MouseInputController(Universe universe)
        {
            if (universe == null)
            {
                throw new ArgumentNullException("universe");
            }
            this.universe = universe;
        }

        // Methods
        /// <summary>
        /// Returns the rotation angle, in radians, corresponding to the given vertical mouse movement.
        /// </summary>
        /// <param name="vertMouseMovement">The number of pixels the mouse has moved in the Y direction.</param>
        /// <returns>The rotation angle, in radians, corresponding to the given vertical mouse movement.</returns>
        private static float GetRotXForMouseMovement(int vertMouseMovement)
        {
            return vertMouseMovement * MouseRotationVerticalMultiplier;
        }
        /// <summary>
        /// Returns the rotation angle, in radians, corresponding to the given horizontal mouse movement.
        /// </summary>
        /// <param name="vertMouseMovement">The number of pixels the mouse has moved in the X direction.</param>
        /// <returns>The rotation angle, in radians, corresponding to the given horizontal mouse movement.</returns>
        private static float GetRotYForMouseMovement(int horizMouseMovement)
        {
            return horizMouseMovement * MouseRotationHorizontalMultiplier;
        }
        /// <summary>
        /// Called continuously, handles the input that's been recorded with other event handlers.
        /// </summary>
        /// <param name="timeElapsed">The number of ticks elapsed since this method was last called.</param>
        public void HandleInput(int ticksElapsed)
        {
        }
        /// <summary>
        /// A mouse button was pressed down.
        /// </summary>
        /// <param name="e">A <see cref="T:MouseEventArgs"/> describing the mouse button pressed down.</param>
        public void MouseDown(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                lastMouseLocation = e.Location;
                leftMouseButtonPressed = true;
            }
        }
        /// <summary>
        /// The mouse curser was moved.
        /// </summary>
        /// <param name="e">A <see cref="T:MouseEventArgs"/> describing the mouse movement.</param>
        public void MouseMove(MouseEventArgs e)
        {
            if (leftMouseButtonPressed)
            {
                universe.Navigation.AdjustXRotation(GetRotXForMouseMovement(e.Location.Y - lastMouseLocation.Y));
                universe.Navigation.AdjustYRotation(GetRotYForMouseMovement(e.Location.X - lastMouseLocation.X));
                lastMouseLocation = e.Location;
            }
        }
        /// <summary>
        /// A mouse button was released.
        /// </summary>
        /// <param name="e">A <see cref="T:MouseEventArgs"/> describing the mouse button released.</param>
        public void MouseUp(MouseEventArgs e)
        {
            leftMouseButtonPressed = false;
        }
        /// <summary>
        /// The mouse wheel was moved.
        /// </summary>
        /// <param name="e">A <see cref="T:MouseEventArgs"/> describing the mouse wheel movement.</param>
        public void MouseWheel(MouseEventArgs e)
        {
            universe.Navigation.Zoom = universe.Navigation.Zoom + (e.Delta * MouseWheelZoomMultiplier);
        }
    }
}
