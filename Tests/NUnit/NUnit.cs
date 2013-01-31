using System;
using NUnit.Framework;

namespace ConstellationStation.NUnit
{
    [TestFixture]
    public class NUnit
    {
        [Test]
        public void AlwaysPass()
        {
        }

        [Test]
        public void ConsoleOut()
        {
            Console.WriteLine("Test console output");
        }

        [Test]
        public void Asserts()
        {
            int x = 4;
            int y = 7;

            Assert.IsTrue(x + y == 11);
            Assert.That(x + y == 11);
            Assert.AreEqual(11, x + y);
            Assert.Less(x, y);
        }
    }
}
