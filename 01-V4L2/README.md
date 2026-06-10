# V4L2
> 카메라 없이, V4L2 API만으로 디바이스 열거부터 HW H.264 인코딩까지 검증

## Tasks

### 1. 디바이스 열거
- `/dev/video*` 전체 순회하며 `VIDIOC_QUERYCAP`으로 드라이버명, capability 출력
- capability 플래그 비트 해석 (M2M / CAPTURE / STREAMING 구분)
- `VIDIOC_ENUM_FMT`으로 디바이스별 지원 픽셀 포맷 열거
- video10 / 11 / 12가 각각 디코더 / 인코더 / ISP임을 출력으로 확인

### 2. 픽셀 포맷
- YUV420 테스트 패턴 프레임 직접 생성 (Y 그라데이션 + U/V 색상)
- 같은 패턴을 NV12로 생성 — planar vs semi-planar 메모리 배치 비교
- stride(bytesperline)와 width가 다를 때 발생하는 문제 재현

### 3. H.264 인코딩 (V4L2 M2M)
- `/dev/video11` 인코더 초기화: S_FMT(양쪽 큐) → REQBUFS → mmap → STREAMON
- 테스트 패턴 프레임 투입 → H.264 바이트스트림 회수 → 파일 저장
- `ffplay -f h264`로 재생 검증
- hexdump로 NAL 구조 확인 (Annex B start code, SPS/PPS/IDR)
- Extended Controls 실험: 비트레이트, GOP(I_PERIOD), REPEAT_SEQ_HEADER

### 4. HW vs SW 인코딩 비교
- 동일 YUV 입력을 video11(HW) / libx264(SW)로 각각 인코딩
- CPU 사용률, 프레임당 처리 시간, 동일 비트레이트 화질 비교
- 결과 수치 기록

## References

본 단계는 커널 공식 문서 [Video for Linux API (Part I)](https://www.kernel.org/doc/html/latest/userspace-api/media/v4l/v4l2.html)를
기반으로 진행한다. 외부 라이브러리(live555, GStreamer 등) 및 비공식 튜토리얼에 의존하지 않는다.
