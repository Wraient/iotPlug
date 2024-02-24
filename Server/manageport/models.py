from django.db import models

# Create your models here.
class Appliance(models.Model):
    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=255)
    state = models.BooleanField(default=False)

    def __str__(self):
        return f"{self.id} : {self.state}"
        
