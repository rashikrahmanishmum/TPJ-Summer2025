#ifndef DFPLAYER_H
#define DFPLAYER_H

void dfplayer_init(void);
void dfplayer_play_beep(void);        // Plays short beep (track 1)
void dfplayer_start_music(void);      // Plays session music (track 2)
void dfplayer_stop_music(void);       // Stops music
void dfplayer_resume_music(void);     // Resumes music (or restarts)

#endif