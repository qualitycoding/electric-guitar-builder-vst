# Lesson: long runs must be launched detached, and tool timeouts recycle the box

Two failure modes hit the same task:
1. A shell tool call that exceeds its deadline kills its process group —
   background curls/builds die mid-write, leaving truncated artifacts.
2. /var/tmp is wiped on container recycle; anything needed across calls
   (cmake package, build trees) must be restaged, ideally from .tools.

Rule: launch anything longer than ~2 minutes with `setsid nohup sh script.sh
> log 2>&1 < /dev/null &`, poll the log on subsequent calls, and keep
deliverables and resumable downloads on the persistent mount. Never combine
`curl -C -` with `-r`: on retry the resume offset miscomputes; instead append
the missing tail of a fixed range explicitly.
