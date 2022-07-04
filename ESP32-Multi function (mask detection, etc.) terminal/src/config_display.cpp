#include <config_display.h>
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern int people_index;
#define DESPLAY_SPEED 80               //动画每帧间隔
//以下是绘图部分
void fun1(){
  u8g2.clearBuffer();
  page_1_to_4();
  //显示光标
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(5, 16*(1%4==0? 4:1%4)-4,118);
  u8g2.sendBuffer();
}
void fun2(){
  u8g2.clearBuffer();
  page_1_to_4();
  //显示光标
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(5, 16*(2%4==0? 4:2%4)-4,118);
  u8g2.sendBuffer();
}
void fun3(){
  u8g2.clearBuffer();
  page_1_to_4();
  //显示光标
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(5, 16*(3%4==0? 4:3%4)-4,118);
  u8g2.sendBuffer();
}
void fun4(){
  u8g2.clearBuffer();
  page_1_to_4();
  //显示光标
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(5, 16*(4%4==0? 4:4%4)-4,118);
  u8g2.sendBuffer();
}
void page_1_to_4(){
  u8g2.setFont(u8g2_font_wqy14_t_gb2312a);
  u8g2.setCursor(20, 16*1-2);
  u8g2.print(" ① 主要功能");
  u8g2.setCursor(20, 16*2-2);
  u8g2.print(" ② 网络配置");
  u8g2.setCursor(20, 16*3-2);
  u8g2.print(" ③ 考勤设置");
  u8g2.setCursor(20, 16*4-2);
  u8g2.print(" ④ 关于我们  <1>");
  u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );
}
void page10(){
  u8g2.setFont(u8g2_font_wqy14_t_gb2312a);
  u8g2.setCursor(20, 16*1-2);
  u8g2.print(" ① 人脸识别");
  u8g2.setCursor(20, 16*2-2);
  u8g2.print(" ② 口罩检测");
  u8g2.setCursor(20, 16*3-2);
  u8g2.print(" ③ 健康码检测");
  u8g2.setCursor(20, 16*4-2);
  u8g2.print(" ④ 我的音乐  <2>");
  u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );
}

void fun11(){
  u8g2.clearBuffer();
  page10();
  //显示光标
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(5, 16*(1%4==0? 4:1%4)-4,118);
  u8g2.sendBuffer();
}
void fun12(){
  u8g2.clearBuffer();
  page10();
  //显示光标
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(5, 16*(2%4==0? 4:2%4)-4,118);
  u8g2.sendBuffer();
}
void fun13(){
  u8g2.clearBuffer();
  page10();
  //显示光标
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(5, 16*(3%4==0? 4:3%4)-4,118);
  u8g2.sendBuffer();
}
void fun14(){
  u8g2.clearBuffer();
  page10();
  //显示光标
  u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
  u8g2.drawGlyph(5, 16*(4%4==0? 4:4%4)-4,118);
  u8g2.sendBuffer();
}

void page20(){
  u8g2.clearBuffer();
  u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );
  u8g2.setFont(u8g2_font_wqy14_t_gb2312a);
  u8g2.setCursor(20, 16*1-2);
  u8g2.print(" WIFI名称:");
  u8g2.setCursor(20, 16*2-2);
  u8g2.print(" BAMBOO");
  u8g2.setCursor(20, 16*3-2);
  u8g2.print(" 连接状态:");
  u8g2.setCursor(20, 16*4-2);
  u8g2.print(" 成功");
  u8g2.sendBuffer();
}
void page30(){
  u8g2.clearBuffer();
  u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );
  u8g2.setFont(u8g2_font_wqy14_t_gb2312a);
  u8g2.setCursor(20, 16*1-2);
  u8g2.print("出勤人数:");
  u8g2.setCursor(20, 16*2-2);
  u8g2.print(people_index);
  u8g2.setCursor(20, 16*3-2);
  u8g2.print("打卡天数:");
  u8g2.setCursor(20, 16*4-2);
  u8g2.print("1");
  u8g2.sendBuffer();
}
void page40(){
  u8g2.clearBuffer();
  u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );
  u8g2.setFont(u8g2_font_wqy14_t_gb2312a);
  u8g2.setCursor(20, 16*1-2);
  u8g2.print("系统:FreeRTOS");
  u8g2.setCursor(20, 16*2-2);
  u8g2.print("芯片:ESP32");
  u8g2.setCursor(20, 16*3-2);
  u8g2.print("开发者:BAMBOO");
  u8g2.setCursor(20, 16*4-2);
  u8g2.print("综合设计二");
  u8g2.sendBuffer();
}
void display_hutao(){
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao1 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao2 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao3 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao4 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao5 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao6 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao7 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao8 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao9 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao10 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao11 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 32 , 0 , 64 , 64 , hutao12 );     //128,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
}
void display_mask(){
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 30 , 0 , 67 , 64 , mask1 );     //67,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 30 , 0 , 67 , 64 , mask2 );     //67,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 30 , 0 , 67 , 64 , mask3 );     //67,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 30 , 0 , 67 , 64 , mask4 );     //67,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 30 , 0 , 67 , 64 , mask4 );     //67,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 30 , 0 , 67 , 64 , mask3 );     //67,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 30 , 0 , 67 , 64 , mask2 );     //67,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 30 , 0 , 67 , 64 , mask1 );     //67,64为图片尺寸，根据你的图片尺寸修改
  u8g2.sendBuffer();  // 显示缓冲区内容
  delay(DESPLAY_SPEED);
}
void display_EIE_logo(){
  u8g2.clearBuffer(); // 清空显示缓冲区     
  u8g2.drawXBMP( 20 , 0 , 88 , 64 , logo );     //89,64为图片尺寸，根据你的图片尺寸修改
  u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );
  u8g2.sendBuffer();  // 显示缓冲区内容
}