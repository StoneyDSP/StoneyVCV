# VCA

Voltage-controlled Amplifier.

Supports polyphony.

<picture>
<source srcset="https://raw.githubusercontent.com/StoneyDSP/StoneyVCV/refs/heads/production/res/specs/VCA-dark.svg" media="(prefers-color-scheme: dark)" />
<source srcset="https://raw.githubusercontent.com/StoneyDSP/StoneyVCV/refs/heads/production/res/specs/VCA-light.svg" media="(prefers-color-scheme: light), (prefers-color-scheme: no-preference)" />
<img src="https://raw.githubusercontent.com/StoneyDSP/StoneyVCV/refs/heads/production/res/specs/VCA-dark.svg" height="380px" width="90px" />
</picture>

## Panel

### inputs

#### in

Standard input.

Supports polyphony.

#### cv

Control Voltage input.

Supports polyphony.

### outputs

#### out

Standard output.

Supports polyphony.

### parameters

#### gain

Control voltage gain multiplier.

### lights

#### blink

Shows a smoothed representation of the sum total of the voltage at all `out` ports.
