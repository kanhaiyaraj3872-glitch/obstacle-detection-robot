# Test Plan

Record real observations only. Do not mark tests as passed before running them on the hardware.

| Test ID | Procedure | Expected result | Actual result | Pass/Fail |
|---|---|---|---|---|
| T01 | Power on with motors disconnected | MCU starts and LCD initializes | To record | Pending |
| T02 | Place target at several known distances | Plausible distance shown | To record | Pending |
| T03 | Target farther than threshold | “Path clear” state shown | To record | Pending |
| T04 | Target closer than threshold | Buzzer on and motor stop command issued | To record | Pending |
| T05 | Force sensor timeout safely | Error shown; stop command issued | To record | Pending |
| T06 | Repeat test several times | Behavior remains consistent | To record | Pending |

Include test date, sensor model, target surface, approximate measured distance, supply voltage, and any limitations in your final report.
