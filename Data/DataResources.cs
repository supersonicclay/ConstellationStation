using System;

namespace ConstellationStation.Data
{
    /// <summary>
    /// Provides access to content files required by the application.
    /// </summary>
    public static class DataResources
    {
        // Properties
        /// <summary>
        /// Gets the root folder path of the content.
        /// </summary>
        private static string Root
        {
            get { return AppDomain.CurrentDomain.BaseDirectory + @"\content\"; }
        }
        /// <summary>
        /// Gets the file path to star catalog.
        /// </summary>
        public static string StarCatalog
        {
            get { return Root + "stars.dat"; }
        }
        /// <summary>
        /// Gets the file path to star texture.
        /// </summary>
        public static string StarTexture
        {
            get { return Root + "star.tga"; }
        }
    }
}
