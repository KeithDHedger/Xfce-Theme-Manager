#!/bin/bash

PROGRAM=xfce-theme-manager
LAUNCHER=Xfce-Theme-Manager.desktop
PREFIX=${PREFIX:-"/usr/local"}

mkdir -p "${PREFIX}/bin" "${PREFIX}/share/applications" "${PREFIX}/share/pixmaps"

cp -p "${PROGRAM}" "${PREFIX}/bin"
cp "$LAUNCHER" "${PREFIX}/share/applications"
cp "${PROGRAM}.png" "${PREFIX}/share/pixmaps"


