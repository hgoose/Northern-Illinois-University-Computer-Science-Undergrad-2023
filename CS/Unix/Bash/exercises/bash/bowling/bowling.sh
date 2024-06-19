#!/usr/bin/env bash
error () {
  echo "$1"
  exit 1
}
add_throws () {
  local ball
  (($#)) || error 'Score cannot be taken until the end of the game'
  for ball in ${@} ; do
    ((ball < 0)) && error 'Negative roll is invalid'
    ((frame_score += ball))
  done
}
all_pins () {
  ((frame_score > 10)) && error 'Pin count exceeds pins on the lane'
  ((frame_score == 10))
}
final_score=0
for frame_index in {1..10} ; do
  frame_score=0
  for throw_index in 1 2 ; do
    add_throws $1
    shift
    if all_pins ; then
      if ((frame_index < 10)) ; then
        add_throws ${@:1:3 - throw_index}
        break
      else
        fill=1
        ((final_score += frame_score))
        frame_score=0
      fi
    fi
  done
  if ((fill)) ; then
    add_throws $1
    shift
    all_pins
  fi
  ((final_score += frame_score))
done
(($#)) && error 'Cannot roll after game is over'
echo $final_score

