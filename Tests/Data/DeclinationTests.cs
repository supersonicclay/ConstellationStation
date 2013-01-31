using System;
using ConstellationStation.Common;
using NUnit.Framework;

namespace ConstellationStation.Data
{
    [TestFixture]
    public class DeclinationTests
    {
        [Test]
        public void Constructor()
        {
            new Declination();
        }
        [Test]
        public void PositivePropertyTrue()
        {
            Declination target = new Declination();
            target.Positive = true;
            Assert.AreEqual(true, target.Positive);
        }
        [Test]
        public void PositivePropertyFalse()
        {
            Declination target = new Declination();
            target.Positive = false;
            Assert.AreEqual(false, target.Positive);
        }
        [Test]
        public void DegreesPropertyOptimal()
        {
            Declination target = new Declination();
            target.Degrees = 1;
            Assert.AreEqual(1, target.Degrees);
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void DegreesPropertyTooSmall()
        {
            Declination target = new Declination();
            target.Degrees = -1;
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void DegreesPropertyTooLarge()
        {
            Declination target = new Declination();
            target.Degrees = 91;
        }
        [Test]
        public void MinutesPropertyOptimal()
        {
            Declination target = new Declination();
            target.Minutes = 1;
            Assert.AreEqual(1, target.Minutes);
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void MinutesPropertyTooSmall()
        {
            Declination target = new Declination();
            target.Minutes = -1;
            Assert.AreEqual(-1, target.Minutes);
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void MinutesPropertyTooLarge()
        {
            Declination target = new Declination();
            target.Minutes = 61;
        }
        [Test]
        public void SecondsPropertyOptimal()
        {
            Declination target = new Declination();
            target.Seconds = 0.0f;
            Assert.AreEqual(0.0f, target.Seconds, 0.001f);
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void SecondsPropertyTooSmall()
        {
            Declination target = new Declination();
            target.Seconds = -0.1f;
        }
        [Test]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void SecondsPropertyTooLarge()
        {
            Declination target = new Declination();
            target.Seconds = 60.1f;
        }

        [Test]
        public void ParsePositive()
        {
            Declination target = Declination.Parse("+12 34 56.7");
            Declination expected = new Declination() { Positive = true, Degrees = 12, Minutes = 34, Seconds = 56.7f };
            AssertX.AreEqual(expected, target, 0.01f);
        }

        [Test]
        public void ParseNegative()
        {
            Declination target = Declination.Parse("-12 34 56.7");
            Declination expected = new Declination() { Positive = false, Degrees = 12, Minutes = 34, Seconds = 56.7f };
            AssertX.AreEqual(expected, target, 0.01f);
        }
    }
}
