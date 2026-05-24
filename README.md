# pixel-to-rtsp
> Raspberry Pi에서 V4L2 캡처부터 RTSP 서빙까지, 미디어 파이프라인을 커널 레벨부터 직접 구현해보는 학습 프로젝트


## Motivation

업무에서 DeepStream / GStreamer로 미디어 파이프라인을 다루지만, 프레임워크가 추상화해주는 레이어 아래에서 실제로 무슨 일이 일어나는지는 블랙박스에 가까웠다.

- 카메라 디바이스가 OS에 어떻게 노출되는지 (V4L2)
- 픽셀이 메모리에서 어떻게 배치되는지 (YUV / NV12 / RGB / RGBA)
- HW 인코더가 SW 대비 CPU를 얼마나 줄여주는지
- RTSP 세션이 실제로 어떤 메시지를 주고받는지

## Architecture

```
[Camera] → [V4L2 capture] → [H.264 encode] → [RTSP server] → [Client]
```

## Environment
- Raspberry Pi 4 4B
