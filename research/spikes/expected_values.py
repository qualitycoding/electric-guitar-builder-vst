#!/usr/bin/env python3
import json
from model_spike import mapping
cases = {
 'default': mapping(),
 'short_light': mapping(scale_inches=24, gauge_inches=.008, midi=40),
 'long_heavy': mapping(scale_inches=26.5, gauge_inches=.014, midi=40),
 'angle_depth_mute': mapping(pick_angle_deg=60, pick_depth_mm=3, palm_mute=1),
}
print(json.dumps(cases, indent=2, sort_keys=True))
open(__file__.replace('.py', '.json'), 'w').write(json.dumps(cases, indent=2, sort_keys=True) + '\n')
