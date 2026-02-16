#!/bin/bash

if [[ "$PWD" != *"/traincraft" ]]; then
  echo "This script has to be run from the project root."
  echo "Current working dir: $PWD"
  exit 1
fi

ENGINE_CLASSES_DIR="./core/src/main/java/me/pocolor/traincraft/engine"
ENGINE_INCLUDE_DIR="./engine/include/jni"

find "$ENGINE_CLASSES_DIR" -name "*.java" | while read -r filepath;
do
  name=$(basename "$filepath" .java)
  snake_case=$(echo "$name" | sed 's/\([A-Z]\)/_\L\1/g' | sed 's/^_//')
  target_dir="$ENGINE_INCLUDE_DIR/$snake_case"
  mkdir -p "$target_dir"

  javac -h "$target_dir" "$filepath"
done

find "$ENGINE_CLASSES_DIR" -name "*.class" -delete