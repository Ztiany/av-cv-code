#include "playthread.h"

#include <QDebug>
#include <QFile>
#include <SDL2/SDL.h>

//封装 SDL 函数调用的解决判断，如果调用失败则直接进入 end。
#define END(judge, func)                                                                                                                                                                               \
  if (judge) {                                                                                                                                                                                         \
    qDebug() << #func << "error" << SDL_GetError();                                                                                                                                                    \
    goto end;                                                                                                                                                                                          \
  }

PlayThread::PlayThread(QObject *parent) : QThread(parent) { connect(this, &PlayThread::finished, this, &PlayThread::deleteLater); }

PlayThread::~PlayThread() {
  disconnect();
  requestInterruption();
  quit();
  wait();
  qDebug() << this << "析构了";
}

SDL_Texture *PlayThread::createTexture(SDL_Renderer *renderer) {

  SDL_Texture *texture = SDL_CreateTexture(
      //渲染上下文
      renderer,
      //像素格式
      SDL_PIXELFORMAT_ARGB32,
      // Texture can be used as a render target
      SDL_TEXTUREACCESS_TARGET,
      //纹理的宽高
      50, 50);

  if (!texture) {
    return nullptr;
  }

  // 设置纹理为 renderer 的渲染目标
  if (SDL_SetRenderTarget(renderer, texture)) {
    return nullptr;
  }

  // 设置颜色
  // if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0)) {
  //  return nullptr;
  // }
  // if (SDL_RenderClear(renderer)) {
  //  return nullptr;
  // }

  if (SDL_SetRenderDrawColor(renderer, 189, 255, 0, SDL_ALPHA_OPAQUE)) {
    return nullptr;
  }

  // 画图形
  SDL_Rect rect = {0, 0, 50, 50};
  if (SDL_RenderDrawRect(renderer, &rect)) {
    return nullptr;
  }
  if (SDL_RenderDrawLine(renderer, 0, 0, 50, 50)) {
    return nullptr;
  }
  if (SDL_RenderDrawLine(renderer, 50, 0, 0, 50)) {
    return nullptr;
  }

  return texture;
}

void PlayThread::showClick(SDL_Event &event, SDL_Renderer *renderer, SDL_Texture *texture) {
  SDL_MouseButtonEvent btn = event.button;

  int w = 0;
  int h = 0;

  if (SDL_QueryTexture(texture, nullptr, nullptr, &w, &h)) {
    return;
  }

  int x = btn.x - (w >> 1);
  int y = btn.y - (h >> 1);
  SDL_Rect dstRect = {x, y, w, h};

  // 清除
  if (SDL_RenderClear(renderer)) {
    return;
  }

  // 复制纹理到渲染目标【默认绘制到窗口】
  if (SDL_RenderCopy(renderer, texture, nullptr, &dstRect)) {
    return;
  }

  //    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  //    SDL_RenderDrawRect(renderer, &dstRect);

  // 更新渲染操作到屏幕上
  SDL_RenderPresent(renderer);
}

void PlayThread::run() {

  // 1：声明对象
  SDL_Window *window = nullptr;          // 窗口
  SDL_Renderer *renderer = nullptr;      // 渲染上下文
  SDL_Texture *texture = nullptr;        // 纹理（直接跟特定驱动程序相关的像素数据）
  SDL_Rect dstRect = {100, 100, 50, 50}; // 矩形框

  // 2：初始化子系统
  END(SDL_Init(SDL_INIT_VIDEO), SDL_Init);

  // 3：创建窗口
  window = SDL_CreateWindow(
      // 标题
      "SDL修改渲染目标",
      // x
      SDL_WINDOWPOS_UNDEFINED,
      // y
      SDL_WINDOWPOS_UNDEFINED,
      // w
      500,
      // h
      500, SDL_WINDOW_SHOWN);
  END(!window, SDL_CreateWindow);

  // 4：创建渲染上下文
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    renderer = SDL_CreateRenderer(window, -1, 0);
    END(!renderer, SDL_CreateRenderer);
  }

  // 5：创建纹理
  texture = createTexture(renderer);
  END(!texture, SDL_CreateTextureFromSurface);

  // 6：设置渲染目标为window
  END(SDL_SetRenderTarget(renderer, nullptr), SDL_SetRenderTarget);

  // 7：设置绘制颜色（画笔颜色）
  END(SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE), SDL_SetRenderDrawColor);

  // 8：用绘制颜色（画笔颜色）清除渲染目标【理解为设置框架背景色】
  END(SDL_RenderClear(renderer), SDL_RenderClear);

  // 9：拷贝纹理到渲染目标
  END(SDL_RenderCopy(renderer, texture, nullptr, &dstRect), SDL_RenderCopy);

  // 10：更新所有的渲染操作到屏幕上
  SDL_RenderPresent(renderer);

  // 等待退出事件
  while (!isInterruptionRequested()) {
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
      goto end;
    case SDL_MOUSEBUTTONUP:
      showClick(event, renderer, texture);
      break;
    }
  }

end:
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
