using System;
using System.Collections.Generic;
using Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace ConstellationStation.Graphics
{
    /// <summary>
    /// Draws debugging information.
    /// </summary>
    public class DebugArtist : Artist
    {
        // Constants
        /// <summary>
        /// The duration, in ticks, to show log messages.
        /// </summary>
        private const int LogMessageDuration = 5000;

        // Fields
        /// <summary>
        /// The font used for debug messages.
        /// </summary>
        private Microsoft.DirectX.Direct3D.Font debugFont;
        /// <summary>
        /// Backing store for the log messages.
        /// </summary>
        private static Queue<LogMessage> logMessages = new Queue<LogMessage>();
        /// <summary>
        /// The rectangle representing the 2-d position of the log messages.
        /// </summary>
        private Rectangle logRect;
        /// <summary>
        /// Backing store for the realtime message.
        /// </summary>
        private static string realtimeMessage;
        /// <summary>
        /// The rectangle representing the 2-d position of the realtime message.
        /// </summary>
        private Rectangle realtimeRect;

        // Properties
        /// <summary>
        /// Gets a value indicating if this <see cref="T:DebugArtist"/> is initialized and ready for use.
        /// </summary>
        public override bool IsInitialized
        {
            get { return debugFont != null && realtimeRect != null && logRect != null && logMessages != null; }
        }
        /// <summary>
        /// Gets all the active log messages.
        /// </summary>
        public static string LogMessages
        {
            get
            {
                string log = "";
                foreach (LogMessage message in logMessages)
                {
                    log += message.Message + "\n";
                }
                return log;
            }
        }
        /// <summary>
        /// Gets the real-time debug message that is cleared after every render.
        /// </summary>
        public static string RealtimeMessage
        {
            get { return realtimeMessage; }
        }

        // Methods
        /// <summary>
        /// Add <paramref name="message"/> to the log view.
        /// </summary>
        /// <param name="message">The debug message.</param>
        public static void AddLogMessage(string message)
        {
            lock (logMessages)
            {
                logMessages.Enqueue(new LogMessage(message));
            }
        }
        /// <summary>
        /// Add <paramref name="message"/> to the real-time debug message.
        /// </summary>
        /// <param name="message">The debug message.</param>
        public static void AddRealtimeMessage(string message)
        {
            realtimeMessage = realtimeMessage + message;
        }
        /// <summary>
        /// Add <paramref name="message"/> to the debug string followed by a new line.
        /// </summary>
        /// <param name="message">The debug message.</param>
        public static void AddRealtimeMessageLine(string message)
        {
            realtimeMessage = realtimeMessage + message + "\n";
        }
        /// <summary>
        /// Removes the expired log messages.
        /// </summary>
        private void CleanLog()
        {
            lock (logMessages)
            {
                int currentTicks = Environment.TickCount;
                while (logMessages.Count > 0 && currentTicks - logMessages.Peek().Ticks > LogMessageDuration)
                {
                    logMessages.Dequeue();
                }
            }
        }
        /// <summary>
        /// Initializes this artist. This is called
        /// when the program is first started and also when the device is reset.
        /// </summary>
        protected override void InitializeArtist()
        {
            debugFont = new Microsoft.DirectX.Direct3D.Font(Device, new System.Drawing.Font("Arial", 12));
            realtimeRect = new Rectangle(10,30, 700, 500);
            logRect = new Rectangle(Device.Viewport.Width - 700, 30, 700, 500);
        }
        /// <summary>
        /// Render the components for which this artist is responsible.
        /// </summary>
        /// <param name="ticksElapsed">The number of ticks elapsed since this method was last called</param>
        public override void Render(int ticksElapsed)
        {
            debugFont.DrawText(null, RealtimeMessage, realtimeRect,
                DrawTextFormat.Left | DrawTextFormat.WordBreak | DrawTextFormat.ExpandTabs,
                Color.Yellow);

            debugFont.DrawText(null, LogMessages, logRect,
                DrawTextFormat.Right | DrawTextFormat.WordBreak | DrawTextFormat.ExpandTabs,
                Color.Yellow);

            realtimeMessage = "";
            CleanLog();
        }
    }

    /// <summary>
    /// Structure used to store log messages and when they were logged.
    /// </summary>
    struct LogMessage
    {
        // Fields
        /// <summary>
        /// The tick count at the time this message created.
        /// </summary>
        public int Ticks;
        /// <summary>
        /// The message string.
        /// </summary>
        public string Message;

        // Constructors
        /// <summary>
        /// Creates a new log message using the current tick count and <paramref name="message"/>.
        /// </summary>
        /// <param name="message">The message string.</param>
        public LogMessage(string message)
        {
            this.Ticks = Environment.TickCount;
            this.Message = message;
        }
    }
}
