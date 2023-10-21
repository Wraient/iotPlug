from django.db import models

# Create your models here.
class Appliance(models.Model):
    id = models.AutoField(primary_key=True)
    state = models.BooleanField(default=False)

    def __str__(self):
        return str(self.id) + " : " + str(self.state)