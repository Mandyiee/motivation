#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>  

int main () {
    int resp;

    // Create a video clip
    resp = system("ffmpeg -i 'vee.mp4' -ss 00:30:38 -to 00:32:09 -c copy 'video_clip.mp4'");
    if (resp == -1 || !WIFEXITED(resp) || WEXITSTATUS(resp) != 0)
    {
        fprintf(stderr, "Error: Unable to create video clip.\n");
        return -1;
    }

    // Retrieve the audio clip
    resp = system("ffmpeg -i video_clip.mp4 -q:a 0 -map a audio_clip.mp3");
    if (resp == -1 || !WIFEXITED(resp) || WEXITSTATUS(resp) != 0)
    {
        fprintf(stderr, "Error: Unable to extract audio clip.\n");
        return -1;
    }

    // Merge image and audio to form final video
    resp = system("ffmpeg -loop 1 -i raise.png -i audio_clip.mp3 -c:v libx264 -c:a copy -shortest final.mp4");
    if (resp == -1 || !WIFEXITED(resp) || WEXITSTATUS(resp) != 0)
    {
        fprintf(stderr, "Error: Unable to create final video.\n");
        return -1;
    }

    printf("Video processing completed successfully.\n");
    return 0;
}
