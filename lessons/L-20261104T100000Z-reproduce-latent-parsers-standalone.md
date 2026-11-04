# Lesson: reproduce latent parser bugs standalone before touching the suite

Symptom: T-027 kept failing "P2 reference audio readable" even after the
truncated WAV was replaced with a verified-complete file. The WAV parsed fine
in Python. Copying the exact `readWav` code into a 30-line standalone program
reproduced the failure instantly: fmt-chunk fields were read off by one byte
(tag/ch) and with swapped endianness (bits) — a latent defect from the first
draft that no earlier test had reached because T-027 always failed earlier.

Rule: when a check fails for reasons that don't add up, extract the exact code
path into a minimal standalone reproducer FIRST. Do not assume the surrounding
harness, env vars, or data are at fault, and do not add "defensive" changes to
unrelated code.
