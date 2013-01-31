using System;
using ConstellationStation.Data;
using Microsoft.DirectX.Direct3D;

namespace ConstellationStation.Graphics
{
    /// <summary>
    /// Shared functionality for classes responsible for drawing.
    /// </summary>
    public abstract class Artist
    {
        // Fields
        /// <summary>
        /// Backing store.
        /// </summary>
        private Device device;
        /// <summary>
        /// Backing store.
        /// </summary>
        private Universe universe;

        // Properties
        /// <summary>
        /// Gets or sets the <see cref="T:Device"/> for this <see cref="T:Artist"/>.
        /// </summary>
        protected Device Device
        {
            get { return device; }
            private set { device = value; }
        }
        /// <summary>
        /// Gets a value indicating if this <see cref="T:Artist"/> is initialized and ready for use.
        /// </summary>
        public abstract bool IsInitialized { get; }
        /// <summary>
        /// Gets or sets the <see cref="T:Universe"/> for this <see cref="T:Artist"/>.
        /// </summary>
        protected Universe Universe
        {
            get { return universe; }
            private set { universe = value; }
        }

        // Methods
        /// <summary>
        /// Initializes the properties of this artist and calls <c>InitializeArtist()</c>.
        /// </summary>
        /// <param name="device">A reference to a <see cref="T:Device"/> for this <see cref="T:Artist"/> to use.</param>
        /// <param name="universe">A reference to a <see cref="T:Universe"/> for this <see cref="T:Artist"/> to use.</param>
        /// <exception cref="T:ArgumentNullException"><paramref name="device"/> or <paramref name="universe"/> or <paramref name="input"/> is null.</exception>
        public void Initialize(Device device, Universe universe)
        {
            if (device == null) {
                throw new ArgumentNullException("device");
            }
            if (universe == null) {
                throw new ArgumentNullException("universe");
            }
            this.Device = device;
            this.Universe = universe;
            InitializeArtist();
        }
        /// <summary>
        /// Initializes this artist. This is called
        /// when the program is first started and also when the device is reset.
        /// </summary>
        protected abstract void InitializeArtist();
        /// <summary>
        /// Render the components for which this artist is responsible.
        /// </summary>
        /// <param name="ticksElapsed">The number of ticks elapsed since this method was last called</param>
        public abstract void Render(int ticksElapsed);
    }
}
