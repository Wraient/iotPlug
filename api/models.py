# api/models.py

from django.db import models

class Product(models.Model):
    id = models.AutoField(primary_key=True)  # Automatically added as the primary key
    state = models.BooleanField(default=False)
    # name = models.CharField(max_length=100)
    # description = models.TextField()

    def __str__(self):
        return self.name