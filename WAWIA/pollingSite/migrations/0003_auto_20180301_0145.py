# Generated by Django 2.0.2 on 2018-03-01 01:45

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('pollingSite', '0002_student_lastname'),
    ]

    operations = [
        migrations.AddField(
            model_name='classroom',
            name='end_date',
            field=models.DateField(null=True),
        ),
        migrations.AddField(
            model_name='classroom',
            name='start_date',
            field=models.DateField(null=True),
        ),
    ]
