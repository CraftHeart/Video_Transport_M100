#!/usr/bin/env python
# -*- coding: utf-8 -*-
import cv2

def Camera_Init():
    cv2.namedWindow('Video')
    cv2.setWindowProperty('Video',cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_FULLSCREEN)
    print "camera init sucessed!"

def Camera(cmd):
    capture0 = cv2.VideoCapture(0)
    capture1 = cv2.VideoCapture(2)

    #cv2.namedWindow('Video',cv2.WND_PROP_FULLSCREEN)
#    cv2.namedWindow('Video')
#    cv2.setWindowProperty('Video',cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_FULLSCREEN)

    _, frame0 = capture0.read()
    _, frame1 = capture1.read()

    if cmd == 'c':
        cv2.imshow('Video',frame0)
        cv2.waitKey(10)
    elif cmd == 'v':
        cv2.imshow('Video',frame1)
        cv2.waitKey(10)

#    _, frame0 = capture0.read()
#    _, frame1 = capture1.read()

    cv2.destroyWindow('Video')

