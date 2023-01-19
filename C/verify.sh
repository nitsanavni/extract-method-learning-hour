#!/bin/bash -i

result="$1.result"

eval "$2" > "$result"

git add --intent-to-add "$result"

git diff --quiet "$result" \
    && \
        ( \
            echo ""; \
            echo "  *** $1 test passed ***"; \
            echo ""; \
        ) \
    || \
        ( \
            echo "*** $1 test failed ***"; \
            git add --patch "$result"; \
            false \
        )
