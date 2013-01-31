using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ConstellationStation.Graphics;
using ConstellationStation.Data;

namespace ConstellationStation.UI
{
    /// <summary>
    /// Main frame for the UI.
    /// </summary>
    public partial class MainForm : Form
    {
        // Fields
        /// <summary>
        /// Backing store.
        /// </summary>
        private GraphicsController graphics;
        /// <summary>
        /// Backing store.
        /// </summary>
        private KeyboardInputController keyboardInput;
        /// <summary>
        /// Backing store.
        /// </summary>
        private MouseInputController mouseInput;
        /// <summary>
        /// Backing store.
        /// </summary>
        private Program program;
        /// <summary>
        /// Backing store.
        /// </summary>
        private Universe universe;

        // Constructors
        /// <summary>
        /// Constructs a new instance of the <see cref="T:MainForm"/> class.
        /// </summary>
        public MainForm()
        {
            InitializeComponent();
        }

        // Properties
        /// <summary>
        /// A reference to the graphics controller.
        /// </summary>
        public GraphicsController Graphics
        {
            get { return graphics; }
            internal set { graphics = value; }
        }
        /// <summary>
        /// A reference to the keyboard input controller.
        /// </summary>
        public KeyboardInputController KeyboardInput
        {
            get { return keyboardInput; }
            internal set { keyboardInput = value; }
        }
        /// <summary>
        /// A reference to the mouse input controller.
        /// </summary>
        public MouseInputController MouseInput
        {
            get { return mouseInput; }
            internal set { mouseInput = value; }
        }
        /// <summary>
        /// A reference to the main program.
        /// </summary>
        public Program Program
        {
            get { return program; }
            internal set { program = value; }
        }
        /// <summary>
        /// A reference to the universe.
        /// </summary>
        public Universe Universe
        {
            get { return universe; }
            internal set { universe = value; }
        }

        // Methods
        /// <summary>
        /// Handle the key down event.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:KeyEventArgs"/>.</param>
        private void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            KeyboardInput.KeyDown(e);
        }
        /// <summary>
        /// Handle the key press event.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:KeyPressEventArgs"/>.</param>
        private void MainForm_KeyPress(object sender, KeyPressEventArgs e)
        {
            KeyboardInput.KeyPress(e);
        }
        /// <summary>
        /// Handle the key up event.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:KeyEventArgs"/>.</param>
        private void MainForm_KeyUp(object sender, KeyEventArgs e)
        {
            KeyboardInput.KeyUp(e);
        }
        /// <summary>
        /// Handle the mouse button down event.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:MouseEventArgs"/>.</param>
        private void MainForm_MouseDown(object sender, MouseEventArgs e)
        {
            MouseInput.MouseDown(e);
        }
        /// <summary>
        /// Handle the mouse move event.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:MouseEventArgs"/>.</param>
        private void MainForm_MouseMove(object sender, MouseEventArgs e)
        {
            MouseInput.MouseMove(e);
        }
        /// <summary>
        /// Handle the mouse button up event.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:MouseEventArgs"/>.</param>
        private void MainForm_MouseUp(object sender, MouseEventArgs e)
        {
            MouseInput.MouseUp(e);
        }
        /// <summary>
        /// Handle the mouse wheel event.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:MouseEventArgs"/>.</param>
        private void MainForm_MouseWheel(object sender, MouseEventArgs e)
        {
            MouseInput.MouseWheel(e);
        }
        /// <summary>
        /// Handle the paint event of the form.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:PaintEventArgs"/>.</param>
        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            if (Graphics != null && Graphics.IsGraphicsInitialized)
            {
                Graphics.RenderScene(0);
            }
        }
        /// <summary>
        /// Handle the form resize event.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:EventArgs"/>.</param>
        private void MainForm_Resize(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized || !Visible)
            {
                Program.Pause();
            }
            else
            {
                Program.Resume();
            }
        }
        /// <summary>
        /// Handle the new menu item.
        /// </summary>
        /// <param name="sender">The sender of the event.</param>
        /// <param name="e">The <see cref="T:EventArgs"/>.</param>
        private void NewMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("NEW!!!");
        }

    }
}