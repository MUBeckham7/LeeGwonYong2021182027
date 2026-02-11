# 👋 Unreal Engine 5 C++ Developer

게임을 개발하는 과정에서 발생하는 문제를 해결해온 개발자입니다. 

---

## 🎯 Project1 (With My Ally)

언리얼 엔진을 기반으로 한 2인용 멀티 좀비 게임

![제목 없는 비디오 - Clipchamp로 제작](https://github.com/user-attachments/assets/186369e3-17d1-45f4-b19c-5e9801408be0)

## 🎯 Project2 (The Doldrums)

언리얼 엔진을 기반으로 한 1인 무인동 생존 게임

![제목 없는 비디오 - Clipchamp로 제작 (1)](https://github.com/user-attachments/assets/2261021c-72f0-4c9f-8b93-8fc736190311)


---

# 🧠 Problem → Analysis → Solution → Result

---

## 🤖 Environment Query System(EQS)

### 🔎 Problem
**Behavior Tree AI의 한계**

### 🛠 Solution
- EQS기반 위치 평가
- Score가중치 설계

### 🚀 Result
- 환경 장애물을 인식하여 객체의 위치선정 능력 향상

<img width="725" height="346" alt="image" src="https://github.com/user-attachments/assets/c51a83c2-4ea5-4535-816d-57919807a868" />

---

## 🌫 Volumetric Fog를 대체하기 위한 HLSL을 기반으로 한 Fog 제작
WithMyAlly,Unreal,C++\Source\WMA\Shader\PPmaterialFog.usf

### 🔎 Problem
- 적 객체의 EQS 사용으로 인한 비용 증가로 프로그램 무게 증가
- 비용 연산이 많은 Volumetric Fog로 인한 프로그램 무게 증가

### 🛠 Solution
- Post Processing Volume을 활용

### 🔎 Problem
- Post Processing Volume으로 인한 Texture가 1차원적으로 제한됨

### 🛠 Solution
- Noise Texture를 다중으로 겹처 안개를 다층적으로 표현

### 🔎 Problem
- 캐릭터가 안개를 거닐때 안개가 카메라를 따라 이동해오는 문제 발생
- 캐릭터가 안개속을 지나다니는 느낌이 아닌 안개가 캐릭터를 지나가는 문제발생

### 🛠 Solution
- 구와 직선의 교차점 공식을 이용하여 카메라와 안개(구)의 거리를 계산하여 위치 보정
- 노이즈 텍스쳐의 위치를 삼선형 보간을 통해 보정하여 문제 해결


https://github.com/user-attachments/assets/0c0af798-ec92-44bd-807e-b6b4cb5a3392


### 🚀 Result
- EQS를 사용하여 증가한 그래픽 처리 비용을 안개 처리 비용에서 감소시킴으로서 게임 안정성 향상



---

## 🌲 GeneratedDynamicMesh를 활용하여 나무 파괴

LeeGwonYong2021182027\The Doldrums,Unreal5,C++\Prop\DDGeneratedDynamicMeshActorLog.cpp

### 🔎 Problem
- Decal 방식을 사용한 나무파괴는 실루엣 변화가 없어 몰입 방해
- StaticMesh는 런타임 도중 변형해야하는 문제

### 🛠 Solution
- StaticMesh를 DynamicMesh로 변환하여 런타임도중에도 변환가능하도록 구현

### 🔎 Problem
- Static Mesh(도끼)와 겹쳐진 DynamicMesh(나무)의 영역을 제거해야함

### 🛠 Solution
- 영역 연산을 더 정확하게 하기 위해 DynamicMesh를 Tessellation을 이용하여 더 많은 버텍스를 생성
- 많아진 버텍스를 활용하여 Boolean 연산

---
<img width="1037" height="651" alt="스크린샷 2026-02-11 171457" src="https://github.com/user-attachments/assets/d6b0ff0b-0e41-4e0c-8a20-9a6f3c813f77" />  
<img width="1021" height="683" alt="스크린샷 2026-02-11 171541" src="https://github.com/user-attachments/assets/f1b1dd50-8398-4cd1-b00b-85a68a62a85b" />

---
![제목 없는 비디오 - Clipchamp로 제작 (2)](https://github.com/user-attachments/assets/83cca3ab-e91b-4646-8cc4-e59e5478f3c6)
---


### 🚀 Result
- 객체끼리 서로 부딪힐때만 Tessellation과 Boolean 연산을 하여 게임의 프레임을 향상시키지 않음.
---

## 🪓 데이터 기반 장비 시스템 설계

### 🔎 Problem
- 직접적인 Mesh 교체 방식은 확장성 부족
- 런타임 로딩 문제

### 🛠 Solution
- SoftObjectPtr기반 설계
- LoadSynchronous 처리

### 🚀 Result
- 안정적인 장착/해제 시스템 구현

---



---

# 🛠 Technical Skills

### Engine
- Unreal Engine 5
- Gameplay Framework
- Collision & Physics System
- Niagara
- Animation Notify
- EQS
- Post Process Pipeline

### Programming
- C++
- HLSL
- Material System
- Ray–Sphere Intersection Mathematics

---

# 🚀 Goal

To become a developer who understands the engine deeply  
and solves structural problems that arise during game development.
