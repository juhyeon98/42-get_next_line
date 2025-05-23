# get_next_line
## 진행 기간
- 2023.04 - 2023.05
## 소개
- 42 커리큘럼의 두번째 과제 중 하나이며, 파일을 읽어 한 문장씩 반환하는 함수 `get_next_line` 을 구현하는 프로젝트 입니다.
## 주요 기능
- 함수의 시그니처는 다음과 같습니다.
```c
char *get_next_line(int fd);
```
- 매개변수 `fd` 스트림을 읽어, 스트림에서 추출한 문자열에서 한 줄 단위로 읽어 반환합니다.
- 반복적으로 호출되는 경우, 다음 문장을 반환하도록 합니다.
- 만일 스트림에서 읽을 데이터가 없거나 모두 다 읽은 경우에는 `NULL`을 반환합니다.
- 테스트 중에 버퍼의 크기를 변경할 수 있어야 하며, 버퍼 크기에 상관없이 모두 예상대로 작동해야 합니다.
## 어려웠던 점
### 1. "한 줄"에 대해서
- 단순히 "한 줄을 읽는다"라는 것을 실제 코드로 구현하는 것이 까다로웠습니다.
- "한 줄"에 대한 정의와 문자열 흐름에 따라 다양한 경우의 수를 정리해야 했습니다.
- 그리고 그 경우의 수에 따라 알맞게 처리해야 했습니다.
### 2. 버퍼 단위로 읽는 문제
- 해당 과제는 버퍼 단위로 읽어야 하는 구조를 따라야 했습니다.
- 이때 발생할 수 있는 문제는 버퍼 안에 여러 개의 "한 줄"이 들어올 수 도 있고, "한 줄"이 여러 번의 `read` 를 통해 들어올 수 있었습니다.
- 이러한 모든 상황을 고려해서 문자열에서 "한 줄"을 추출해야 했습니다.
### 3. 메모리 누수 문제
- 매 호출마다 누적적으로 버퍼에서 읽은 문자열을 저장하는 변수가 필요 했습니다.
- 해당 변수는 버퍼처럼 실행에 따라 길이가 달라져야 했기 때문에 메모리 할당을 할 수 밖에 없었습니다.
- 이때, 해당 변수가 사용되고 난 뒤 언제 `free`를 사용해야 할지가 메모리 누수에 있어서 관건이었습니다.
## 해결한 방법
### 1. "한 줄"에 대한 정의
- 이 문제를 해결하기 위해 "한 줄"이라는 것을 다음과 같이 정의 했습니다.
  1. 개행까지의 문자열
  2. 개행이 없는 경우, 파일 끝까지의 문자열
- 이러한 정의를 통해 버퍼로 읽어온 문자열에서 개행을 확인하는 로직을 추가함으로써, "한 줄"을 건너 뛰고 추출하는 문제를 방지할 수 있었습니다.
### 2. 경우의 수 정리
- 버퍼에 저장된 문자열에 대해서 다음과 같은 경우의 수가 있습니다.
  1. 버퍼에 개행이 포함되어 있는 경우
  2. 버퍼에 개행이 없는 경우
  3. 파일을 다 읽어, 버퍼가 비어 있는 경우
- 버퍼에 개행이 몇 개가 존재하든지, 첫번째로 발견되는 개행만을 고려했습니다.
- 개행이 발견 되고 나면, 개행까지의 문자열을 반환하고 나머지 문자열을 다시 재 탐색하도록 처리 했습니다.
- 만일 버퍼에 개행이 없는 경우에는 누적 저장 변수에 모두 저장하고 다시 읽어오도록 했습니다.
- 이들을 반복문을 통해 "한 줄"을 찾을 때까지 - 버퍼가 가득 차있는 동안에만 반복하도록 했습니다.
- 만일 파일에서 더이상 읽을 것이 없는 경우, 버퍼가 비워지므로 반복문을 탈출해 누적 저장 변수의 것들을 반환하도록 했습니다.
### 3. 사용 중지 지점
- 버퍼의 문자열을 누적 저장하는 변수를 더 이상 사용하지 않는 부분을 확인했습니다.
- 전체 구조에서 버퍼의 누적 저장 변수가 사용되지 않는 부분은 저장된 값을 반환할 때 였습니다.
- 따라서, 개행을 찾아 "한 줄"을 반환 할 때와 파일을 모두 읽고 난 뒤에 "한 줄"을 반환 할 때 `free`를 사용해 메모리 누수를 막을 수 있었습니다.
