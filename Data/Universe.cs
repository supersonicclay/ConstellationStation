
namespace ConstellationStation.Data
{
    /// <summary>
    /// Representation of the universe; I know, it's ambitious. :) It is intended to
    /// contain all data classes.
    /// </summary>
    public class Universe
    {
        // Fields
        /// <summary>
        /// Backing store.
        /// </summary>
        private Navigation navigation;
        /// <summary>
        /// Backing store.
        /// </summary>
        private bool showDebug = false;
        /// <summary>
        /// Backing store.
        /// </summary>
        private bool showMockup = false;
        /// <summary>
        /// Backing store.
        /// </summary>
        private Starfield starfield;

        // Properties
        /// <summary>
        /// Gets the user's navigation information.
        /// </summary>
        public Navigation Navigation
        {
            get { return navigation; }
        }
        /// <summary>
        /// Gets whether or not to show debug information.
        /// </summary>
        public bool ShowDebug
        {
            get
            {
#if DEBUG
                return showDebug;
#else
                return false;
#endif
            }
            set
            {
#if DEBUG
                showDebug = value;
#endif
            }
        }
        /// <summary>
        /// Whether or not to show the mockup on the screen.
        /// </summary>
        public bool ShowMockup
        {
            get
            {
#if DEBUG
                return showMockup;
#else
                return false;
#endif
            }
            set
            {
#if DEBUG
                showMockup = value;
#endif
            }
        }
        /// <summary>
        /// Gets a collection of distant objects such as stars and galaxies.
        /// </summary>
        public Starfield Starfield
        {
            get { return starfield; }
        }

        // Methods
        /// <summary>
        /// Initializes this <see cref="T:Universe"/> with new data.
        /// </summary>
        public void NewUniverse()
        {
            navigation = new Navigation();
            starfield = new Starfield();
            starfield.NewStarfield();
        }
    }
}
