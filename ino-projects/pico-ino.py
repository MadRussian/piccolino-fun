#!/usr/bin/env python

import argparse
import sys, os

MODEL="pro5v328"

if __name__ == "__main__":
  parser = argparse.ArgumentParser('Pico Ino',
    description='Run ino build/upload with the correct model for the Piccolino')
  parser.add_argument('action', help='The action to perform',
    choices=['build','upload'])
  args = parser.parse_args()

  if (args.action == 'build' or
      args.action == 'upload'):
    os.system('ino {} -m {}'.format(args.action, MODEL))
  else:
    os.system('ino {}'.foramt(args.action))
