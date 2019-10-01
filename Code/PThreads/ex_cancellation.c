/*
 * Deferred cancellation and asyncronous cancellation test
 *
 * This demo creates an high priority thread that creates 2 low priority
 * threads that execute with round robin and with fifo
 *
 * Copyright (C) 2002 by Paolo Gai
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <stdio.h>
#include <pthread.h>


void my_message(void *arg)
{
  printf("KILLED!!!\n");
}

int i;

void *thread(void *arg)
{
  i = 0;

  pthread_cleanup_push(my_message, NULL);

  if (arg)
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

  for (; i<500000000; i++); /* busy wait */

  pthread_testcancel();

  pthread_cleanup_pop(0);

  printf("Not killed!!!\n");

  return NULL;
}

int main()
{
  pthread_t mythread;

  pthread_attr_t myattr;

  int err;

  /* creates a thread with deferred cancellation */

  pthread_attr_init(&myattr);
  err = pthread_create(&mythread, &myattr, thread, NULL);
  pthread_attr_destroy(&myattr);
  pthread_join(mythread, NULL);
  printf("No cancellation: i=%d\n",i);

  pthread_attr_init(&myattr);
  err = pthread_create(&mythread, &myattr, thread, NULL);
  pthread_attr_destroy(&myattr);
  pthread_cancel(mythread);
  pthread_join(mythread, NULL);
  printf("With cancellation (deferred): i=%d\n",i);

  pthread_attr_init(&myattr);
  err = pthread_create(&mythread, &myattr, thread, (void *)1);
  pthread_attr_destroy(&myattr);
  pthread_cancel(mythread);
  pthread_join(mythread, NULL);
  printf("With cancellation (asynchronous): i=%d\n",i);

  return 0;
}
