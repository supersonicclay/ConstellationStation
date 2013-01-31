
using ConstellationStation.Math;
namespace ConstellationStation.Data
{
    /// <summary>
    /// Stores information about the user's navigation about the universe.
    /// </summary>
    public class Navigation
    {
        // Constants
        /// <summary>
        /// Multiplier to apply to x-axis rotations when at max zoom.
        /// </summary>
        private const float MaxZoomXRotationMultiplier = 0.25f;
        /// <summary>
        /// Multiplier to apply to y-axis rotations when at max zoom.
        /// </summary>
        private const float MaxZoomYRotationMultiplier = 0.25f;

        // Fields
        /// <summary>
        /// Backing store for the rotation about the x axis.
        /// </summary>
        private float xRotation = 0.4278f;
        /// <summary>
        /// Backing store for the rotation about the y axis.
        /// </summary>
        private float yRotation = 1.0f;
        /// <summary>
        /// Backing store for the zoom.
        /// </summary>
        private float zoom;

        // Properties
        /// <summary>
        /// Gets or sets the rotation about the X axis.
        /// The value is limited to -PI/2 to PI/2 (inclusive).
        /// </summary>
        public float XRotation
        {
            get { return xRotation; }
            set
            {
                xRotation = value;
                xRotation = (float)System.Math.Min(xRotation, System.Math.PI / 2.0);
                xRotation = (float)System.Math.Max(xRotation, -System.Math.PI / 2.0);
            }
        }
        /// <summary>
        /// Gets or sets the rotation about the Y axis.
        /// The value is wrapped around to keep the value between 0 and PI*2 (inclusive).
        /// </summary>
        public float YRotation
        {
            get { return yRotation; }
            set
            {
                if (value > System.Math.PI * 2.0)
                {
                    yRotation = (float)(value - (System.Math.PI * 2.0) * System.Math.Truncate(value / (System.Math.PI * 2.0)));
                }
                else if (value < 0.0f)
                {
                    yRotation = (float)(value + (System.Math.PI * 2.0) * (System.Math.Truncate(value / (System.Math.PI * 2.0)) + 1));
                }
                else
                {
                    yRotation = value;
                }
            }
        }
        /// <summary>
        /// Gets or sets the zoom ratio.
        /// The value is limited to 0 to 1 (inclusive).
        /// </summary>
        public float Zoom
        {
            get { return zoom; }
            set
            {
                zoom = value;
                zoom = System.Math.Min(zoom, 1.0f);
                zoom = System.Math.Max(zoom, 0.0f);
            }
        }

        // Methods
        /// <summary>
        /// Adjust the x-axis rotation by the given amount.
        /// The adjustment is inversely proportional to the zoom
        /// (i.e. the higher the zoom, the less the rotation is altered).
        /// </summary>
        /// <param name="delta">The amount, in radians, to adjust the x-axis rotation.</param>
        public void AdjustXRotation(float delta)
        {
            float multiplier = Interpolations.Lerp(Zoom, 1.0f, MaxZoomXRotationMultiplier);
            XRotation += multiplier * delta;
        }
        /// <summary>
        /// Adjust the y-axis rotation by the given amount.
        /// The adjustment is inversely proportional to the zoom
        /// (i.e. the higher the zoom, the less the rotation is altered).
        /// </summary>
        /// <param name="delta">The amount, in radians, to adjust the y-axis rotation.</param>
        public void AdjustYRotation(float delta)
        {
            float multiplier = Interpolations.Lerp(Zoom, 1.0f, MaxZoomYRotationMultiplier);
            YRotation += multiplier * delta;
        }
    }
}
