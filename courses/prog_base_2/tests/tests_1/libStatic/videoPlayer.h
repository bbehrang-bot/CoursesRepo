#ifndef VIDEOPLAYER_H_INCLUDED
#define VIDEOPLAYER_H_INCLUDED
#define MIN_CAPACITY 2
typedef enum VIDEOPLAYER_STATUS
{VIDEOPLAYER_NOT_INIT,VIDEOPLAYER_STOP,VIDEOPLAYER_PAUSE,VIDEOPLAYER_PLAY,VIDEOPLAYER_NULL_PTR} VIDEOPLAYER_STATUS;
typedef struct videoPlayer_s videoPlayer_t;
typedef struct film_s film_t;
videoPlayer_t * videoPlayer_new();
void videoPlayer_free(videoPlayer_t * self);
film_t * film_new(char filmName[100],int id);
void film_print(film_t * self);
typedef struct list_s * list_t;

list_t list_new();
void list_delete(list_t list);

void list_insert(list_t list, film_t * film, int index);
void list_remove(list_t list, int index);

int list_get_element(list_t list, int index);
int list_get_size(list_t list);
void list_print(list_t list);
void videoPlayer_print(videoPlayer_t * vidPlayer);
void videoPlayer_play(videoPlayer_t * vidPlayer,int index);

#endif // VIDEOPLAYER_H_INCLUDED
