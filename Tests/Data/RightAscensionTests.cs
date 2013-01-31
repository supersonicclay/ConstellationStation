using System;
using ConstellationStation.Common;
using NUnit.Framework;

namespace ConstellationStation.Data
{
    [TestFixture]
    public class RightAscensionTests
    {
        [Test]
        public void Constructor()
        {
            new RightAscension();
        }
        [Test]
        public void HoursPropertyOptimal()
        {
            RightAscension target = new RightAscension();
            target.Hours = 1;
            Assert.AreEqual(1, target.Hours);
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void HoursPropertyTooSmall()
        {
            RightAscension target = new RightAscension();
            target.Hours = -1;
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void HoursPropertyTooLarge()
        {
            RightAscension target = new RightAscension();
            target.Hours = 25;
        }
        [Test]
        public void MinutesPropertyOptimal()
        {
            RightAscension target = new RightAscension();
            target.Minutes = 1;
            Assert.AreEqual(1, target.Minutes);
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void MinutesPropertyTooSmall()
        {
            RightAscension target = new RightAscension();
            target.Minutes = -1;
            Assert.AreEqual(-1, target.Minutes);
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void MinutesPropertyTooLarge()
        {
            RightAscension target = new RightAscension();
            target.Minutes = 61;
        }
        [Test]
        public void SecondsPropertyOptimal()
        {
            RightAscension target = new RightAscension();
            target.Seconds = 0.0f;
            Assert.AreEqual(0.0f, target.Seconds, 0.001f);
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void SecondsPropertyTooSmall()
        {
            RightAscension target = new RightAscension();
            target.Seconds = -0.1f;
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void SecondsPropertyTooLarge()
        {
            RightAscension target = new RightAscension();
            target.Seconds = 60.1f;
        }

        [Test]
        public void Parse()
        {
            RightAscension target = RightAscension.Parse("12 34 56.7");
            RightAscension expected = new RightAscension() { Hours = 12, Minutes = 34, Seconds = 56.7f };
            AssertX.AreEqual(expected, target, 0.01f);
        }
    }
}
