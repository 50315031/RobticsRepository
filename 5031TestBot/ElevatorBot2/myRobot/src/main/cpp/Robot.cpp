/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/livewindow/LiveWindow.h>
#include <frc/Talon.h>

class Robot : public frc::TimedRobot {
 public:
  Robot() {
    m_robotDrive.SetExpiration(0.1);
    m_timer.Start();
  }

  void AutonomousInit() override {
    m_timer.Reset();
    m_timer.Start();
  }

  void AutonomousPeriodic() override {
    // Drive for 2 seconds
    if (m_timer.Get() < 2.0) {
      // Drive forwards half speed
      m_robotDrive.ArcadeDrive(-0.5, 0.0);
    } else {
      // Stop robot
      m_robotDrive.ArcadeDrive(0.0, 0.0);
    }
  }

  void TeleopInit() override 
  {
    m_left.SetSpeed(0.5);
    m_right.SetSpeed(0.5);
  }

  void TeleopPeriodic() override {
    // Drive with arcade style (use right stick)
    m_robotDrive.TankDrive(l_stick.GetY(), r_stick.GetY());
  }

  void TestPeriodic() override {}

 private:
  // Robot drive system
  frc::Talon m_left{4};
  frc::Talon m_right{5};
  frc::DifferentialDrive m_robotDrive{m_left, m_right};

  frc::Joystick l_stick{0};
  frc::Joystick r_stick{1};
  frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
  frc::Timer m_timer;
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
