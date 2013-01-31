using System;

namespace ConstellationStation.Graphics
{
    /// <summary>
    /// Calculates frames per second.
    /// </summary>
    public class FpsCounter
    {
        // Constants
        /// <summary>
        /// The number of milliseconds to wait before updating the fps calculation.
        /// </summary>
        private const int FpsUpdateInterval = 1000;

        // Fields
        /// <summary>
        /// Frames per second.
        /// </summary>
        private float fps = 0.0f;
        /// <summary>
        /// The number of frames that have occured since the last update.
        /// </summary>
        private int framesSinceLastUpdate = 0;
        /// <summary>
        /// The tick count when the last update occured.
        /// </summary>
        private int lastUpdateTime = 0;

        // Methods
        /// <summary>
        /// Called with every frame to computer frames per second.
        /// </summary>
        /// <returns></returns>
        public float CalculateFPS()
        {
            // Increment the number of frames that have occured since the last calculation
            ++framesSinceLastUpdate;

            // If it is time to recalculate
            int currentTicks = Environment.TickCount;
            if (currentTicks - lastUpdateTime > FpsUpdateInterval)
            {
                // fps = frames / milliseconds * 1000
                fps = (float)framesSinceLastUpdate / (currentTicks - lastUpdateTime) * 1000;
                lastUpdateTime = currentTicks;
                framesSinceLastUpdate = 0;
            }

            return fps;
        }
    }
}
