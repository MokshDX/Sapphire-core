# Sapphire Core

Sapphire Core is a standalone emulator core (“gem”) focused on modeling real hardware with exact, deterministic behavior.

It is designed to achieve cycle-accurate, pixel-accurate, and timing-accurate emulation by separating hardware behavior from the underlying simulation kernel that advances time and enforces execution order.

Sapphire Core is usable on its own, embeddable in larger applications, and designed to integrate into high-fidelity emulation systems.

---

## Emulation Philosophy

Sapphire Core prioritizes correctness over convenience.

The goal is not to approximate hardware behavior, but to reproduce it exactly—such that running real hardware side-by-side with the emulator produces indistinguishable results at the level of cycles, pixels, and observable signals.

This includes:

- exact instruction timing
- precise interrupt behavior
- correct bus contention and wait states
- hardware-accurate video and audio output
- faithful reproduction of undocumented quirks

---

## Separation of Concerns

Sapphire Core does not own simulated time.

Time advancement and execution ordering are controlled externally by a deterministic simulation kernel. Sapphire Core reacts to this execution environment by translating each step into hardware-accurate behavior.

This separation ensures:

- reproducible execution
- correct causality
- no reliance on host timing
- no frame-based shortcuts

---

## Connectivity and Interaction

Sapphire Core is designed with real-world interaction in mind.

Planned capabilities include:

- hardware-faithful link cable emulation
- online connectivity modeled as physical signaling with latency
- cross-device and cross-generation communication
- interaction with real consoles and original cartridges

Games should behave as if they are communicating with real hardware, regardless of whether that hardware is emulated or physical.

---

## Accuracy and Performance

Accuracy is non-negotiable.

Performance optimizations may exist, but they must preserve exact observable behavior. Any mode that trades correctness for speed must be explicit and opt-in.

The reference behavior of Sapphire Core is intended to match real hardware exactly.

---

## Scope and Status

This project is in early development.

Current focus is on:
- defining correct architectural boundaries
- modeling hardware structure faithfully
- establishing timing and ordering correctness before optimization

No system-specific emulation logic has been implemented yet.

---

## Design Philosophy Summary

If real hardware and the emulator disagree, the emulator is wrong.

Sapphire Core exists to eliminate that disagreement.
