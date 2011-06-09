using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CarLibrary1
{
  
        // Which type of music player does this car have?
        public enum MusicMedia
        {
            musicCd,
            musicTape,
            musicRadio,
            musicMp3
        }

        // Represents the state of the engine.
        public enum EngineState
        { engineAlive, engineDead }

        // The abstract base class in the hierarchy.
        public abstract class Car1
        {
            public string PetName { get; set; }
            public int CurrentSpeed { get; set; }
            public int MaxSpeed { get; set; }

            protected EngineState egnState = EngineState.engineAlive;
            public EngineState EngineState
            { get { return egnState; } }

            public abstract void TurboBoost();

            public Car1()
            {
                MessageBox.Show("CarLibrary Version 2.0!");
            }
            public Car1(string name, int maxSp, int currSp)
            {
                MessageBox.Show("CarLibrary Version 2.0!");
                PetName = name; MaxSpeed = maxSp; CurrentSpeed = currSp;
            }

            public void TurnOnRadio(bool musicOn, MusicMedia mm)
            {
                if (musicOn)
                    MessageBox.Show(string.Format("Jamming {0}", mm));
                else
                    MessageBox.Show("Quiet time...");
            }

        }
    }

