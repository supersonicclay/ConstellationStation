using NUnit.ConsoleRunner;

namespace ConstellationStation.TestRunner
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] consoleRunnerArgs = new string[2];
            consoleRunnerArgs[0] = TestRunnerSettings.Default.UnitTestsPath;
            consoleRunnerArgs[1] = "/wait";
            Runner.Main(consoleRunnerArgs);
        }
    }
}
